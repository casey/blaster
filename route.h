#import "indirect.h"

struct route_t {
  using args_t = map<string, string>;

  route_t();
  virtual ~route_t();

  virtual string         path()                                    = 0;
  virtual view_t& operator()(window_t& window, const args_t& args) = 0;
  virtual vector<string> params() {
    return {}; 
  }

  string arg(const args_t& args, int index);
};

struct routes_t {
  using iterator_t = indirect_iterator_t<route_t>;
  iterator_t begin();
  iterator_t end();
};

extern routes_t routes;
