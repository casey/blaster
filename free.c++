#import "rmr.h"
#import "sym.h"

[[noreturn]] bool rmr_die(const string &msg) {
  rmr.die(msg);
}

const sym_t& null_sym() {
  static sym_t sym{};
  return sym;
}
