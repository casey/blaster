#import "wave.h"
#import "rec.h"
#import "rmr.h"
#import "timer.h"
#import "dollar.h"
#import <atomic>
#import <fftw3.h>

// todo:
//   . try expanding out waveform
//   . try aligning on first zero crossing
//   . figure out the window size which shows all the frequencies that people can hear
//   . equal loudness frequency weighting
//   . fixed phase offsets
//   . perceptually adjusted intensity
//   . A(x)=1/[y(X)]
//   . smoothed intensity
//   . relative intensity

constexpr size_t S = wave_t::sample_count;
constexpr size_t F = wave_t::frequency_count;
constexpr size_t O = S / 2 + 1;

struct fft_t {
  fft_t()
    : plan          (fftw_plan_dft_r2c_1d(S, in,  out,       FFTW_ESTIMATE)),
      phaseless_plan(fftw_plan_dft_c2r_1d(S, out, phaseless, FFTW_ESTIMATE))
  { }
  ~fft_t() { fftw_destroy_plan(plan); fftw_destroy_plan(phaseless_plan); }
  fftw_plan    plan;
  fftw_plan    phaseless_plan;
  double       in       [S];
  fftw_complex out      [O];
  double       phaseless[S];
};

template<int size>
void hann(double(&_)[size]) {
  for (int i = 0; i < size; i++) {
    _[i] *= 0.5 * (1.0 - cos(rmr.tau() * double(i) / size));
  }
}

template<int size>
void scale(double(&_)[size], double factor) {
  for (int i = 0; i < size; i++) {
    _[i] *= factor;
  }
}

template<typename T, int size>
void copy(T(&dst)[size], T(&src)[size]) {
  for (int i = 0; i < size; i++) {
    dst[i] = src[i];
  }
}

static void update_channel(channel_t& c, fft_t& f) {
  copy(f.in, c.waveform);
  hann(f.in);

  fftw_execute(f.plan);

  double sum = 0;
  int i = 0;
  for (auto& _ : c.frequency) {
    fftw_complex& out = f.out[i + 1];
    double R = out[0];
    double I = out[1];
    double M = sqrt(R * R + I * I);
    _ = M;
    sum += M;
    i++;
  }
  c.intensity = sum / i;

  for (int i = 0; i < O; i++) {
    fftw_complex& out = f.out[i];
    double R = out[0];
    double I = out[1];
    double M = sqrt(R * R + I * I);
    if (i > (F >> 4)) {
      out[0] = 0;
      out[1] = 0;
    } else {
      out[0] = M / 2;
      out[1] = M / 2;
    }
  }

  fftw_execute(f.phaseless_plan);

  for (int i = 0; i < S; i++) {
    c.phaseless[S - 1 - i] = f.phaseless[(i + S / 2) % S] / S;
  }
}
static constexpr size_t rec_window = 512;

struct wave_t::data_t {
  unique_ptr<rec_t>         rec;
  channel_t                 l;
  channel_t                 r;
  channel_t                 m;
  float                     l_input[S]     { };
  float                     r_input[S]     { };
  fft_t                     l_fft          { };
  fft_t                     r_fft          { };
  std::atomic_uint_fast64_t input_version  {0};
  uint_fast64_t             output_version {0};

  data_t() {
    rmr.info("wave: initializing");
    rec = std::make_unique<rec_t>(rec_window, [&](rec_t::update_t& u) {
      if (!u.ok) return;

      for (int i = 0; i < S - rec_window; i++) {
        l_input[i] = l_input[i + rec_window];
        r_input[i] = r_input[i + rec_window];
      }

      for (int i = 0; i < rec_window; i++) {
        if (u.left)  l_input[i + S - rec_window] = u.left [i];
        if (u.right) r_input[i + S - rec_window] = u.right[i];
      }
      input_version++;
    });
  }

  void update() {
    if (output_version == input_version) return;

    do {
      output_version = input_version;
      for (int i = 0; i < S; i++) {
        l.waveform[i] = l_input[i];
        r.waveform[i] = r_input[i];
      }
    } while(output_version != input_version);

    update_channel(l, l_fft);
    update_channel(r, r_fft);

    for (int i = 0; i < S; i++) {
      m.waveform [i] = (l.waveform [i] + r.waveform [i]) / 2;
      m.phaseless[i] = (l.phaseless[i] + r.phaseless[i]) / 2;
    }
    for (int i = 0; i < F; i++) {
      m.frequency[i] = (l.frequency[i] + l.frequency[i]) / 2;
    }
    m.intensity = (l.intensity + r.intensity) / 2;
  }
};

wave_t::wave_t() : __(*new data_t) {
}

wave_t::~wave_t() {
  rmr.info("wave: shutting down");
  delete &__;
}

u64              wave_t::version() { __.update(); return __.output_version;      }
bool             wave_t::empty()   { __.update(); return __.output_version == 0; }
const channel_t& wave_t::l    ()   { __.update(); return __.l;                   }
const channel_t& wave_t::r    ()   { __.update(); return __.r;                   }
const channel_t& wave_t::m    ()   { __.update(); return __.m;                   }
