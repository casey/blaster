struct event_t {
  event_t();
  virtual ~event_t() = default;
  virtual void operator()(target_t&) const = 0;
  operator bool() const;
  double time;
  bool   cancelled;
};

struct tick_e : event_t {
  tick_e();
  tick_e next() const;
  void operator()(target_t&) const override;
  tick_e operator++(int);
  bool first() const;
  double elapsed() const;
  double dt;
  u64    count;
};

struct render_e : event_t {
  render_e(tick_e& tick);
  void operator()(target_t&) const override;
  tick_e& tick;
};

struct draw_e : event_t {
  void operator()(target_t&) const override;
  draw_e(tick_e&);
  tick_e& tick;
  int w = 0;
  int h = 0;
  int x = 0;
  int y = 0;
};

struct quit_e   : event_t { void operator()(target_t&) const override; };
struct rename_e : event_t { void operator()(target_t&) const override; };
struct hide_e   : event_t { void operator()(target_t&) const override; };
struct show_e   : event_t { void operator()(target_t&) const override; };

struct modded_e : event_t {
  bool shift   = false;
  bool control = false;
  bool alt     = false;
  bool super   = false;
};

struct key_e : modded_e {
  int  key      = 0;
  int  scancode = 0;
  bool up       = false;
  bool down     = false;
  bool repeat   = false;
};

struct mousemove_e : event_t {
  void operator()(target_t&) const override;
  mousemove_e(double x, double y) : x(x), y(y) { }
  double x;
  double y;
};

struct mouse_e : modded_e {
  int button = 0;
};

struct character_e : event_t {
  character_e(int codepoint);
  int codepoint;
  char str[MB_LEN_MAX + 1];
  void operator()(target_t&) const override;
};

struct resize_e : event_t {
  void operator()(target_t&) const override;
  resize_e(double width, double height) : width(width), height(height) { }
  double width;
  double height;
};

struct scroll_e : event_t {
  void operator()(target_t&) const override;
  scroll_e(double x, double y) : x(x), y(y) { }
  float x;
  float y;
};

#import "gizmo.h"

struct push_e : event_t {
  void operator()(target_t& target) const override;
  push_e(int type, gizmo_t gizmo, double value) : type(type), gizmo(gizmo), value(value) { }

  bool down() const;
  bool up  () const;
  bool set () const;
  
  int      type;
  gizmo_t gizmo;
  double  value;
};

struct    mouseup_e : mouse_e { void operator()(target_t&) const override; }; 
struct  mousedown_e : mouse_e { void operator()(target_t&) const override; }; 
struct mouseenter_e : event_t { void operator()(target_t&) const override; }; 
struct mouseleave_e : event_t { void operator()(target_t&) const override; }; 
struct     verify_e : event_t { void operator()(target_t&) const override; }; 
struct    keydown_e :   key_e { void operator()(target_t&) const override;   keydown_e(); };
struct      keyup_e :   key_e { void operator()(target_t&) const override;     keyup_e(); };
struct  keyrepeat_e :   key_e { void operator()(target_t&) const override; keyrepeat_e(); };
