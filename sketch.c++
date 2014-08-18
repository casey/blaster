#import "sketch.h"
#import "rmr.h"

static bool& frozen() {
  static bool _ = false;
  return _;
}

static vector<sketch_f>& storage() {
  static vector<sketch_f> _;
  return _;
}

void register_sketch(sketch_f f) {
  frozen() && rmr.die("sketch.add: sketch registry is frozen");
  storage().push_back(f);
}

sketches_t sketches;

sketch_f* sketches_t::begin() {
  frozen() = true;
  return &*storage().begin();
}

sketch_f* sketches_t::end() {
  frozen() = true;
  return &*storage().end();
}
