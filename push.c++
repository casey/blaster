#import "push.h"
#import "rmr.h"
#import "event.h"
#import "fmt.h"
#import "portmidi.h"
#import "once.h"
#import "counter.h"
#import "timer.h"

// need to update display, but can't do it every frame
// keep a fixed buffer of uint8s
// send a line every N seconds
// raw 68 x 4 buffer
// 4x68 buffers

template<typename T>
struct check_t {
  explicit check_t(const T& expected) : expected(expected) { }

  check_t& operator<<(const T& actual) {
    actual == expected || rmr.error("check: expected % but actually %"_fmt(expected, actual));
    return *this;
  }

private:
  T expected;
};

template<typename T>
struct maybe_t {
  static_assert(std::is_trivial<T>::value, "maybe: type not trivial");
  maybe_t(whatever_t) : _valid(false)            { }
  maybe_t(          ) : _valid(false)            { }
  maybe_t(const T& _) : _valid( true), _value(_) { }

  bool valid() const {
    return _valid;
  }

  T value() const {
    _valid || rmr.die("maybe.value: invalid");
    return _value;
  }

private:
  bool _valid;
  T    _value;
};

check_t<PmError>& pm_check() {
  static check_t<PmError> _(pmNoError);
  return _;
}

struct pm_initializer_t : counter_t<pm_initializer_t> {
  pm_initializer_t() {
    if (solo()) {
      rmr.info("push: initializing portmidi...");
      pm_check() << Pm_Initialize();
    }
  }

  ~pm_initializer_t() {
    if (solo()) {
      rmr.info("push: terminating portmidi...");
      pm_check() << Pm_Terminate();
    }
  }
};

PmTimestamp time_proc(void*) {
  return rmr.ms();
}

struct zstr_t {
  zstr_t(const char* s) : s(s) { }

  bool operator==(const zstr_t& rhs) {
    return strcmp(s, rhs.s) == 0;
  }

  bool operator!=(const zstr_t& rhs) {
    return !(*this == rhs);
  }

private:
  const char* s;
};

struct midi_t {
  u8     type;
  u8     data1;
  u8     data2;
  double time;
};

ostream& operator<<(ostream& o, const midi_t& msg) {
  return o << (int)msg.type << " " << (int)msg.data1 << " " << (int)msg.data2;
}

struct push_t::data_t : pm_initializer_t {
  data_t(target_t& target) : target(target) {
    input = output = nullptr;
    refresh();

    for(auto& c : display_buffer) {
      c = ' ';
    }
  }

  ~data_t() {
    if (input ) Pm_Close(input );
    if (output) {
      for (int i = 0; i < 64; i++) {
        midi_t msg;
        msg.type  = 144;
        msg.data1 = i + 36;
        msg.data2 = 0;
        write(msg);
      }

      static u8 clear_line[] = {240, 71, 127, 21, 255, 0, 0, 247};
      for (int i = 0; i < 4; i++) {
        clear_line[4] = 28 + i;
        Pm_WriteSysEx(output, 0, clear_line);
      }
      rmr.sleep(0.01);
      Pm_Close(output);
    }
  }

  target_t& target;
  void*     input;
  void*     output;
  uint      next_line = 0;
  timer_t   display_limiter;
  u8        display_buffer[68 * 4];

  void refresh() {
    for (int i = 0; (!input || !output) && i < Pm_CountDevices(); i++) {
      auto info = Pm_GetDeviceInfo(i);
      zstr_t push_name = "Ableton Push User Port";
      bool is_push = push_name == info->name;

      if (is_push && info->input && !input) {
        pm_check() << Pm_OpenInput(&input, i, nullptr, 1024, &time_proc, nullptr);
      }

      if (is_push && info->output && !output) {
        pm_check() << Pm_OpenOutput(&output, i, nullptr, 1024, &time_proc, nullptr, 0);


        static u8 set_slider_mode[] = {240,71,127,21, 99, 0, 1, 6, 247};
        Pm_WriteSysEx(output, 0, set_slider_mode);

        for (int i = 0; i < 64; i++) {
          midi_t msg;
          msg.type  = 144;
          msg.data1 = i + 36;
          msg.data2 = 104;
          write(msg);
        }
      }
    }

    if (output && display_limiter.elapsed() > (1.0 / 30)) {
      static u8 set_line[] = {
        240, 71, 127, 21, 255, 0, 69, 0,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
        45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
        59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        247
      };

      set_line[4] = next_line + 24;
      
      for (int j = 0; j < 68; j++) {
        set_line[j + 8] = display_buffer[j + next_line * 68];
      }

      Pm_WriteSysEx(output, 0, set_line);

      next_line = (next_line + 1) % 4;
      display_limiter.reset();
    }
  }

  bool read(midi_t& msg) {
    if (input) {
      auto err = Pm_Poll(input);

      if (err == pmGotData) {
        PmEvent e;
        int count = Pm_Read(input, &e, 1);

        if (count == 1) {
          msg.type  = Pm_MessageStatus(e.message);
          msg.data1 = Pm_MessageData1(e.message);
          msg.data2 = Pm_MessageData2(e.message);
          msg.time  = e.timestamp / 1000.0;
          return true;
        }
      } else if (err != pmNoData) {
        Pm_Close(input);
        input = nullptr;
      }
    }

    return false;
  }

  bool write(midi_t msg) {
    if (output) {
      PmEvent e;
      e.message   = Pm_Message(msg.type, msg.data1, msg.data2);
      e.timestamp = msg.time;
      auto err = Pm_Write(output, &e, 1);
      if (!err) {
        return true;
      } else {
        Pm_Close(output);
        output = nullptr;
      }
    }

    return false;
  }
};

push_t::push_t(target_t& target) : __(*new data_t{target}) {
}

push_t::~push_t() {
  delete &__;
}

struct pattern_t {
  pattern_t(maybe_t<u8> type, maybe_t<u8> data1, maybe_t<u8> data2) : type(type), data1(data1), data2(data2) { }

  maybe_t<u8> type;
  maybe_t<u8> data1;
  maybe_t<u8> data2;

  bool match(const midi_t& msg) const {
    return (type .valid() ? msg.type  == type .value() : true)
      &&   (data1.valid() ? msg.data1 == data1.value() : true)
      &&   (data2.valid() ? msg.data2 == data2.value() : true);
  }
};

constexpr int cell_count    = 64;
constexpr int button_count  = 64;
constexpr int knob_count    = 11;
constexpr int slider_widget = cell_count + button_count + knob_count;
constexpr int cell_base     = 36;

// order: cells, buttons, knobs, slider

gizmo_t note_to_gizmo(u8 note) {
  if (note >= cell_base && note < cell_base + cell_count) {
    return (gizmo_t)((note - cell_base) + (int)gizmo_t::cell_first);
  }

  if (note < knob_count) { 
    // flip left and right knobs
    if     (note ==  9) note = 10;
    else if(note == 10) note =  9;
    return (gizmo_t)(note + (int)gizmo_t::knob_first);
  }

  if (note == 12) { // slider
    return gizmo_t::slider;
  }

  rmr.die("unknown note: %"_fmt(note));
}

gizmo_t cc_to_gizmo(u8 cc) {
  // knobs
  if (cc == 14 || cc == 15 || (cc >= 71 && cc <= 79)) {
    if      (cc == 14) cc = 10;
    else if (cc == 15) cc =  9;
    else if (cc >= 71) cc -= 71;
    return note_to_gizmo(cc);
  }

  static std::tuple<int, int, int> ranges[] = {
    {102, 109, 0}, { 20,  27, 0}, { 85,  90, 0}, {116, 119, 0}, {  9,   9, 0}, {  3,   3, 0}, { 36,  43, 0},
    { 29,  29, 0}, { 28,  28, 0}, { 48,  48, 0}, { 50,  50, 0}, { 52,  52, 0}, { 54,  54, 0}, { 56,  56, 0},
    { 58,  58, 0}, { 60,  60, 0}, { 62,  62, 0}, {110, 110, 0}, {112, 112, 0}, {114, 114, 0}, { 49,  49, 0},
    { 51,  51, 0}, { 53,  53, 0}, { 55,  55, 0}, { 57,  57, 0}, { 59,  59, 0}, { 61,  61, 0}, { 63,  63, 0},
    {111, 111, 0}, {113, 113, 0}, {115, 115, 0}, { 47,  47, 0}, { 44,  44, 0}, { 46,  46, 0}, { 45,  45, 0}
  };

  static once_t once;
  if (once) {
    int base = 0;
    for (auto& t : ranges) {
      std::get<2>(t) = base;
      base += std::get<1>(t) - std::get<0>(t) + 1;
    }
  }

  for (auto& t : ranges) {
    if (cc >= std::get<0>(t) && cc <= std::get<1>(t)) {
      return (gizmo_t)(cc - std::get<0>(t) + std::get<2>(t) + (int)gizmo_t::button_first);
    }
  }

  rmr.die("push: unknown control code: %"_fmt(cc));
}

double slider_value(u8 data1, u8 data2) {
  u16 x = (data2 << 7) | data1;
  return x / (double)(0b1111'11111'11111);
}

double aftertouch_value(u8 data2) {
  return data2 / (double)127;
}

double turn_down_value(gizmo_t g, u8 data2) {
  auto _ = $(g);

  if (_.button()) {
    return 0.0;
  } else if (_.knob()) {
    if (data2 < 64) {
      return data2 * 1.0;
    } else {
      return data2 - 128.0;
    }
  }

  rmr.die("turn_down_value: strange gizmo: %"_fmt(g));
}

push_e parse_press (const midi_t& _) {
  gizmo_t gizmo = note_to_gizmo(_.data1);
  double  value = $(gizmo).cell() ? _.data2 / 127.0 : 0.0;
  return {0, gizmo, value};
}

push_e parse_note_off  (const midi_t& _) { return {1, note_to_gizmo(_.data1),                            0.0 }; }
push_e parse_touch_off (const midi_t& _) { return {1, note_to_gizmo(_.data1),                            0.0 }; }
push_e parse_button_off(const midi_t& _) { return {1,   cc_to_gizmo(_.data1),                            0.0 }; }
push_e parse_aftertouch(const midi_t& _) { return {2, note_to_gizmo(_.data1),      aftertouch_value(_.data2) }; }
push_e parse_slider    (const midi_t& _) { return {2,        gizmo_t::slider, slider_value(_.data1, _.data2) }; }

push_e parse_turn_down (const midi_t& _) {
  auto g = cc_to_gizmo(_.data1);
  int  t = $(g).knob() ? 2 : 0;
  return {t, g, turn_down_value(g, _.data2)};
}

void push_t::operator()(const tick_e& tick) {
  __.refresh();

  for(midi_t msg; __.read(msg);) {
    static const auto X = rmr.whatever();
    static const std::pair<pattern_t, push_e(*)(const midi_t&)> parsers[] = {
      {{128, X,   0}, parse_note_off  },
      {{144, X,   0}, parse_touch_off },
      {{144, X,   X}, parse_press     },
      {{160, X,   X}, parse_aftertouch},
      {{176, X,   0}, parse_button_off},
      {{176, X,   X}, parse_turn_down },
      {{224, X,   X}, parse_slider    }
    };

    for (auto& parser : parsers) {
      if (parser.first.match(msg)) {
        push_e e = parser.second(msg);

        if ($(e.gizmo).cell()) {
          if (e.down()) {
            //on(e.gizmo);
          } else if(e.up()) {
            //off(e.gizmo);
          }
        } else if ($(e.gizmo).button()) {
          midi_t response = msg;

          if (e.down()) {
            response.data2 = 10;
          } else if(e.up()) {
            response.data2 = 0;
          }

          __.write(response);
        }
          
        e(__.target);
        break;
      }
    }
  }
}

void push_t::color(gizmo_t g, uint c) {
  auto _ = $(g);

  _.cell() || rmr.die("push.on: non-cells not implemented");

  midi_t msg;
  msg.type  = 144;
  msg.data1 = _.number() + 36;
  msg.data2 = c;

  __.write(msg);
}

void push_t::on(gizmo_t _) {
  color(_, 3);
}

void push_t::off(gizmo_t _) {
  color(_, 104);
}

void push_t::display(u8 c) {
  for (auto& r : __.display_buffer) {
    r = c;
  }
}

void push_t::display(int x, int y, u8 c) {
  // todo: dirty checking
  if (x < 0 || x >= 68) return;
  if (y < 0 || y >=  4) return;
  __.display_buffer[y * 68 + x] = c % 128;
}

// push color lookup table
// 0x000000 0x1E1E1E 0x7F7F7F 0xFFFFFF 0xFF4C4C 0xFF0000 0x590000 0x190000
// 0xFFBD6C 0xFF5400 0x591D00 0x271B00 0xFFFF4C 0xFFFF00 0x595900 0x191900
// 0x88FF4C 0x54FF00 0x1D5900 0x142B00 0x4CFF4C 0x00FF00 0x005900 0x001900
// 0x4CFF5E 0x00FF19 0x00590D 0x001902 0x4CFF88 0x00FF55 0x00591D 0x001F12
// 0x4CFFB7 0x00FF99 0x005935 0x001912 0x4CC3FF 0x00A9FF 0x004152 0x001019
// 0x4C88FF 0x0055FF 0x001D59 0x000819 0x4C4CFF 0x0000FF 0x000059 0x000019
// 0x874CFF 0x5400FF 0x190064 0x0F0030 0xFF4CFF 0xFF00FF 0x590059 0x190019
// 0xFF4C87 0xFF0054 0x59001D 0x220013 0xFF1500 0x993500 0x795100 0x436400 
// 0x033900 0x005735 0x00547F 0x0000FF 0x00454F 0x2500CC 0x7F7F7F 0x202020
// 0xFF0000 0xBDFF2D 0xAFED06 0x64FF09 0x108B00 0x00FF87 0x00A9FF 0x002AFF 
// 0x3F00FF 0x7A00FF 0xB21A7D 0x402100 0xFF4A00 0x88E106 0x72FF15 0x00FF00 
// 0x3BFF26 0x59FF71 0x38FFCC 0x5B8AFF 0x3151C6 0x877FE9 0xD31DFF 0xFF005D
// 0xFF7F00 0xB9B000 0x90FF00 0x835D07 0x392B00 0x144C10 0x0D5038 0x15152A
// 0x16205A 0x693C1C 0xA8000A 0xDE513D 0xD86A1C 0xFFE126 0x9EE12F 0x67B50F
// 0x1E1E30 0xDCFF6B 0x80FFBD 0x9A99FF 0x8E66FF 0x404040 0x757575 0xE0FFFF
// 0xA00000 0x350000 0x1AD000 0x074200 0xB9B000 0x3F3100 0xB35F00 0x4B1502
