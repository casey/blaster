#import "view.grid.h"

#import "once.h"
#import "gl.h"
#import "img.h"
#import "rmr.h"
#import "vec.h"
#import "fmt.h"
#import "window.h"

#import <OpenGL/gl3.h>

using _ = grid_v&;

struct grid_v::data_t {
  img_t characters;
  vec4  foreground;
  vec4  background;
};

pixel_t get_pixel(float fg, float bg, u32 codepoint) {
  (codepoint < (256 * 256)) || rmr.die("get_pixel: character not ascii: %"_fmt(codepoint));

  pixel_t result;
  result.r = codepoint & 0xFF;
  result.g = 255 - (codepoint >> 8);
  result.b = fg * 255;
  result.a = bg * 255;

  return result;
}

grid_v::grid_v(size_t x, size_t y) : __(*new data_t())  {
  __.characters.resize(x, y);
  __.foreground = {0, 0, 0, 1};
  __.background = {0, 0, 0, 0};
  clear();

  gl()
  .new_tex("font")
  .image("font", read_bits(rmr.cfg("base") + "dat/font.bin", 4096, 4096))
  .new_tex("char")
  .new_vbo("quad")
  .upload_ccw_quad("quad")
  .supplier("rows",    [&](gl_t& gl, sym_t s) { gl.value(s, __.characters.height()); })
  .supplier("columns", [&](gl_t& gl, sym_t s) { gl.value(s, __.characters.width ()); })
  ;
}


_ grid_v::clear() {
  for (auto& pixel : __.characters) {
    pixel = get_pixel(1.0, 0.0, ' ');
  }
  return *this;
}

_ grid_v::foreground(const vec4& c) {
  __.foreground = c;
  return *this;
}

_ grid_v::background(const vec4& c) {
  __.background = c;
  return *this;
}

_ grid_v::set(size_t x, size_t y, float fg, float bg, u32 codepoint) {
  __.characters(x, y) = get_pixel(fg, bg, codepoint);
  return *this;
}

_ grid_v::set(size_t x, size_t y, float fg, float bg, const string& str) {
  return set(x, y, fg, bg, rmr.codepoints(str));
}

_ grid_v::set(size_t x, size_t y, float fg, float bg, const u32string& str) {
  int i = 0;
  for (auto c : str) {
    if (x + i >= __.characters.width()) break;
    set(x + i, y, fg, bg, c);
    i++;
  }
  return *this;
}

void grid_v::operator()(const draw_e& e) {
  // todo: generalize this instead of being a special case for grid_v
  if (hidden()) return;

  gl()
  .image("char", __.characters)
  .prepare("grid")
  .pack({"position"}, "quad")
  .value("font", "font")
  .value("char", "char")
  .value("foreground", __.foreground)
  .value("background", __.background)
  .ready()
  .triangles()
  .draw_arrays()
  .done()
  ;
}
