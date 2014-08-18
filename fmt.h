#import "str.h"

struct fmt_t {
  fmt_t(const char*);
  string operator%(str_t);

  template<typename... Items>
  string operator()(Items... items) {
    return (*this)({((str_t)items).str()...});
  }

  string operator()(init_t<string>);

  void insert(const string&);

private:
  const char* format;
};

fmt_t operator""_fmt(const char*, size_t);
