#import "top.h"
#import "img.h"

extern "C" {
  struct _CGLContextObject;
  typedef struct _CGLContextObject* CGLContextObj;
}

struct window_t : top_t {
  using _ = window_t&;
  window_t(const hints_t& hints);
  virtual ~window_t();

  bool current() const;
  _ current(bool);

  CGLContextObj& core_context();

  bool closing();
  _ closing(bool);
  img_t screenshot();
  int  width()  const;
  int  height() const;
  uvec2 size() const;
  _ size(int width, int height);
  _ left(int);
  _ top(int);
  _ position(int, int);
  _ beat();
  int left();
  int top();
  gl_t& gl();
  syphon_t& syphon();
  nav_t&  nav();
  void operator()(const   tick_e&) override;
  void operator()(const render_e&) override;
  void operator()(const   draw_e&) override;
  void operator()(const rename_e&) override;
  void operator()(const   show_e&) override;
  void operator()(const   hide_e&) override;
  void operator()(const verify_e&) override;
private:
  struct data_t;
  data_t& __;
};
