#import "space.h"
#import "rmr.h"
#import "window.h"
#import "fmt.h"

using _ = space_t&;

struct space_t::data_t {
  hints_t hints;
};

space_t::space_t() : __(*new data_t) {
  reset_hints();
}

space_t::~space_t() {
  delete &__;
}

hints_t& space_t::hints() {
  return __.hints;
}

space_t& space_t::reset_hints() {
  __.hints = hints_t();
  return *this;
}

void space_t::operator()(const verify_e&) {
  for (auto& child : *this) child.as<window_t>();
}

window_t& space_t::spawn_window() {
  return spawn<window_t>(hints());
}
