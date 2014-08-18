#import "view.h"

struct program_v : view_t {
  program_v(const sym_t& program);
  void operator()(const draw_e&) override;
private:
  struct data_t;
  data_t& __;
};
