#import "top.h"

struct hints_t {
  int    width        = 0;       // maximum width
  int    height       = 0;       // maximum height
// int    red_bits     = 8;
// int    green_bits   = 8;
// int    blue_bits    = 8;
// int    alpha_bits   = 8;
// int    depth_bits   = 24;
// int    stencil_bits = 8;
// int    refresh_rate = 60;
  int    left         = 0;
  int    top          = 0;
  bool   fullscreen   = false;
  bool   hidden       = false;
  bool   resizable    = true;
  bool   decorated    = true;
  string title        = "";
};

struct space_t : top_t {
  using _ = space_t&;
  space_t();
  virtual ~space_t();
  window_t& spawn_window();
  hints_t& hints();
  _ reset_hints();
  void operator()(const verify_e&) override;
private:
  struct data_t;
  data_t& __;
};
