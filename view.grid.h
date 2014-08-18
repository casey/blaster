#import "view.h"

struct grid_v : view_t {
  using _ = grid_v&;
  grid_v(size_t x, size_t y);
  _ set(size_t x, size_t y, float fg, float bg, u32 codepoint);
  _ set(size_t x, size_t y, float fg, float bg, const string& str);
  _ set(size_t x, size_t y, float fg, float bg, const u32string& str);
  _ clear();
  _ foreground(const vec4& c);
  _ background(const vec4& c);
  void operator()(const draw_e&) override;
private:
  struct data_t;
  data_t& __;
};
