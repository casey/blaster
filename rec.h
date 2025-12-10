namespace portaudio {
  class AutoSystem;
  class FunCallbackStream;
}

struct rec_t {
  struct update_t {
    double adc_time;
    double current_time;
    double dac_time;
    bool   input_underflow;
    bool   input_overflow;
    bool   output_underflow;
    bool   output_overflow;
    bool   priming_output;
    bool   ok;
    uint   frame_count;
    float* left;
    float* right;
    uint   result;
    void   complete();
    void   abort   ();
  };

  typedef fun_t<void(update_t&)> callback_t;

  rec_t(uint frame_count, callback_t f);
  ~rec_t();

  const callback_t& callback();

  int channels();

private:
  callback_t                    _callback;
  int                           _channels;
  portaudio::AutoSystem*        auto_sys;
  portaudio::FunCallbackStream* stream;
};
