struct wave_t {
  static constexpr size_t sample_count    = 1 << 10;
  static constexpr size_t frequency_count = sample_count / 2;

  wave_t();
  ~wave_t();

  bool empty();
  u64 version();
  const channel_t& l();
  const channel_t& r();
  const channel_t& m();
private:
  struct data_t;
  data_t& __;
};

struct channel_t {
  double waveform [wave_t::sample_count   ]{};
  double frequency[wave_t::frequency_count]{};
  double phaseless[wave_t::sample_count   ]{};
  double intensity                         {};
};
