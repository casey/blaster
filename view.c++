#import "view.h"
#import "gl.h"
#import "rmr.h"
#import "window.h"
#import "color.h"

using _ = view_t&;

struct view_t::data_t {
  data_t(gl_t& gl) : gl(gl) { }
  gl_t& gl;
};

top_t& first_ancestor(top_t& node, fun_t<bool(top_t&)> pred) {
  if (pred(node)) return node;
  if (node.is_root()) rmr.die("first_ancestor: hit root");
  return first_ancestor(node.parent(), pred);
}

gl_t& find_context(top_t& node) {
  return first_ancestor(node, [](top_t& _) { return _.is<window_t>(); }).as<window_t>().gl();
}

view_t::view_t() : __(*new data_t(find_context(*this).spawn())) {
}

view_t::~view_t() {
  // todo: delete &__.gl;
  delete &__;
}

gl_t& view_t::gl() {
  return __.gl;
}

void view_t::operator()(const verify_e& e) {
  bool found = false;
  for_ancestors([&found](top_t& ancestor) {
    if (ancestor.is<window_t>()) {
      found = true;
    }
  });
  found || rmr.die("view.verify: must have a window as ancestor");
}

void view_t::operator()(const draw_e& e) {
  gl()
  .aperture(e.x, e.y, e.w, e.h)
  .clear_color("blue"_color)
  .clear();
}
