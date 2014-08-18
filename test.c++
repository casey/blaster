#import "test.h"
#import "rmr.h"
#import "fmt.h"

struct test_t {
  void (*function)();
  string name;
  string file;
  int line;
};

int test_failures = 0;

out_t assert_function(const char* expr, bool value, bool fatal, const char* file, int line, const char* macro_name) {
  if (value) return rmr.null();
  cerr << rmr.ansi_red() << "%(%): "_fmt(macro_name, expr);
  test_failures++;
  return fatal ? rmr.fatal() : rmr.pretty();
};

vector<test_t>* test_registry;

auto_register_t::auto_register_t(void (*function)(), string name, string file, int line) {
  static vector<test_t> _;
  test_registry = &_;
  test_registry->push_back({function, name, file, line});
}

void run_tests() {
  if (test_registry) {
    for(auto& t : *test_registry) {
      t.function();
    }
  }
}
