#import "top.h"

struct view_t : top_t {
  using _ = view_t&;
  view_t();
  virtual ~view_t();
  void operator()(const draw_e&) override;
  void operator()(const verify_e&) override;
  int width();
  int height();
protected:
  gl_t& gl();
private:
  struct data_t;
  data_t& __;
};
