#import "str.h"

struct out_t {
  using _ = out_t&;
  out_t();
  out_t(out_t&);
  out_t(out_t&&);
  ~out_t();
  _ operator<<(str_t);
  _ operator,(str_t);
  _ arm();
  _ disarm();
  _ off();
  _ on();
  explicit operator bool();
private:
  bool used;
  bool null;
  bool last;
  bool fatal;
};
