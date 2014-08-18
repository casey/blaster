#import "gizmo.h"

struct push_t {
  push_t(target_t&);
  ~push_t();
  void operator()(const tick_e&);
  void color(gizmo_t, uint);
  void on(gizmo_t);
  void off(gizmo_t);
  void display(int x, int y, u8 c);
  void display(u8 c);
private:
  struct data_t;
  data_t& __;
};
