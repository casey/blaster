#import "rmr.h"
#import "view.h"

#define SKETCH_NAME TOKEN_PASTE(sketch, __COUNTER__)

#define SKETCH static sketch_t SKETCH_NAME = [](view_t& _) -> view_t& 

using sketch_f = fun_t<view_t&(view_t&)>;

struct sketches_t {
  sketch_f* begin();
  sketch_f* end();
};

extern sketches_t sketches;

void register_sketch(sketch_f);

struct sketch_t {
  template<typename T>
  sketch_t(const T& f) {
    register_sketch(sketch_f{f});
  }
};
