#import "route.h"
#import "rmr.h"
#import "fmt.h"
#import "window.h"
#import "sketch.h"
#import "view.program.h"
#import "sym.h"

static vector<route_t*>& storage() {
  static vector<route_t*> _;
  return _;
}

routes_t routes;

void register_route(route_t& r) {
  storage().push_back(&r);
}

route_t::route_t() {
  register_route(*this);
}

route_t::~route_t() {
}

routes_t::iterator_t routes_t::begin() { return iterator_t(&*storage().begin()); }
routes_t::iterator_t routes_t::end  () { return iterator_t(&*storage().end  ()); }

string route_t::arg(const args_t& args, int index) {
  auto p = params();

  if (index < 0 || index >= p.size()) {
    rmr.die("route.args: index out of bounds: %"_fmt(index));
  }

  string& key = p[index];

  if (!args.count(key)) {
    rmr.die("arg: missing key: %"_fmt(key));
  }

  return args.at(key);
}

struct test_r : route_t {
  string path() override { return "test"; }
  view_t& operator()(window_t& window, const map<string, string>& args) override {
    return window.spawn<program_v>("test");
  }
} test_r_instance;

struct program_r : route_t {
  string path() override { return "program"; }
  vector<string> params() override { return { "program" }; }
  view_t& operator()(window_t& window, const map<string, string>& args) override {
    return window.spawn<program_v>(arg(args, 0));
  }
} program_r_instance;

struct sketch_r : route_t {
  string path() override { return "sketch"; }
  view_t& operator()(window_t& window, const map<string, string>& args) override {
    auto& v = window.spawn<view_t>();
    for (auto sketch : sketches) {
      sketch(v);
    }
    return v;
  }
} sketch_r_instance;
