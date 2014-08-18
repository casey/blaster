#import "event.h"

struct target_t {
  virtual void operator()(const       tick_e&) = 0;
  virtual void operator()(const     render_e&) = 0;
  virtual void operator()(const       draw_e&) = 0;
  virtual void operator()(const       quit_e&) = 0;
  virtual void operator()(const     rename_e&) = 0;
  virtual void operator()(const     resize_e&) = 0;
  virtual void operator()(const       hide_e&) = 0;
  virtual void operator()(const       show_e&) = 0;
  virtual void operator()(const  character_e&) = 0;
  virtual void operator()(const    mouseup_e&) = 0;
  virtual void operator()(const  mousedown_e&) = 0;
  virtual void operator()(const  mousemove_e&) = 0;
  virtual void operator()(const mouseenter_e&) = 0;
  virtual void operator()(const     scroll_e&) = 0;
  virtual void operator()(const mouseleave_e&) = 0;
  virtual void operator()(const    keydown_e&) = 0;
  virtual void operator()(const      keyup_e&) = 0;
  virtual void operator()(const  keyrepeat_e&) = 0;
  virtual void operator()(const     verify_e&) = 0;
  virtual void operator()(const       push_e&) = 0;
};

struct null_target_t : target_t {
  void operator()(const       tick_e&) override { }
  void operator()(const     render_e&) override { }
  void operator()(const       draw_e&) override { }
  void operator()(const       quit_e&) override { }
  void operator()(const     rename_e&) override { }
  void operator()(const     resize_e&) override { }
  void operator()(const       hide_e&) override { }
  void operator()(const       show_e&) override { }
  void operator()(const  character_e&) override { }
  void operator()(const    mouseup_e&) override { }
  void operator()(const  mousedown_e&) override { }
  void operator()(const  mousemove_e&) override { }
  void operator()(const mouseenter_e&) override { }
  void operator()(const     scroll_e&) override { }
  void operator()(const mouseleave_e&) override { }
  void operator()(const    keydown_e&) override { }
  void operator()(const      keyup_e&) override { }
  void operator()(const  keyrepeat_e&) override { }
  void operator()(const     verify_e&) override { }
  void operator()(const       push_e&) override { }
};

struct debug_target_t : target_t {
  void operator()(const       tick_e&) override;
  void operator()(const     render_e&) override;
  void operator()(const       draw_e&) override;
  void operator()(const       quit_e&) override;
  void operator()(const     rename_e&) override;
  void operator()(const     resize_e&) override;
  void operator()(const       hide_e&) override;
  void operator()(const       show_e&) override;
  void operator()(const  character_e&) override;
  void operator()(const    mouseup_e&) override;
  void operator()(const  mousedown_e&) override;
  void operator()(const  mousemove_e&) override;
  void operator()(const mouseenter_e&) override;
  void operator()(const     scroll_e&) override;
  void operator()(const mouseleave_e&) override;
  void operator()(const    keydown_e&) override;
  void operator()(const      keyup_e&) override;
  void operator()(const  keyrepeat_e&) override;
  void operator()(const     verify_e&) override;
  void operator()(const       push_e&) override;
};
