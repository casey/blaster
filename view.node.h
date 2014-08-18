#import "view.h"

struct node_v : view_t {
  using _ = node_v&;
  node_v();
  ~node_v();
  void operator()(const draw_e&) override;
  node_t& scene();
  node_t& eye();
  node_t& root();
private:
  struct data_t;
  data_t& __;
};
