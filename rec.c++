#import "rec.h"
#import "rmr.h"
#import "str.h"
#import "fmt.h"

#import "portaudiocpp/PortAudioCpp.hxx"

using update_t = rec_t::update_t;

void update_t::complete() { result = 1; }
void update_t::abort   () { result = 2; }

static int record_callback(
  const void*                     input,
  void*                           output,
  unsigned long                   numframes,
  const PaStreamCallbackTimeInfo* timeinfo,
  PaStreamCallbackFlags           statusFlags,
  void*                           userData
) {
  rec_t& r(*(rec_t*)userData);

  if (r.callback()) {
    rec_t::update_t u{};
    u.adc_time         = timeinfo->inputBufferAdcTime;
    u.dac_time         = timeinfo->outputBufferDacTime;
    u.current_time     = timeinfo->currentTime;
    u.input_underflow  = statusFlags & paInputUnderflow;
    u.input_overflow   = statusFlags & paInputOverflow;
    u.output_underflow = statusFlags & paOutputUnderflow;
    u.output_overflow  = statusFlags & paOutputOverflow;
    u.priming_output   = statusFlags & paPrimingOutput;
    u.frame_count      = numframes;
    u.left             = r.channels() > 0 ? ((float**)input)[0] : nullptr;
    u.right            = r.channels() > 1 ? ((float**)input)[1] : nullptr;
    u.ok               = !(
      u.input_underflow || u.input_overflow  || u.output_underflow || u.output_overflow || u.priming_output
    );
    u.result           = 0;

    r.callback()(u);
    return u.result;
  }

  return 0;
}


const rec_t::callback_t& rec_t::callback() { return _callback; }

int rec_t::channels() { return _channels; }

rec_t::rec_t(uint frame_count, callback_t c) : _callback(c), auto_sys(new portaudio::AutoSystem) {
  auto& input = portaudio::System::instance().defaultInputDevice();
  rmr.info("rec: using input stream: %"_fmt(input.name()));

  _channels = std::min(2, input.maxInputChannels());

  portaudio::DirectionSpecificStreamParameters inParamsRecord(
    input
  , _channels
  , portaudio::FLOAT32
  , false
  , input.defaultLowInputLatency()
  , NULL);

  portaudio::StreamParameters paramsRecord(
    inParamsRecord
  , portaudio::DirectionSpecificStreamParameters::null()
  , 44100.0
  , frame_count
  , 0);

  stream = new portaudio::FunCallbackStream(paramsRecord, record_callback, this);
  stream->start();
};

rec_t::~rec_t() {
  delete stream;
  delete auto_sys;
};
