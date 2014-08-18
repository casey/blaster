#import "fmt.h"
#import "rmr.h"

fmt_t::fmt_t(const char* s) : format(s) {};

string fmt_t::operator%(str_t _) {
  return (*this)({_.str()});
}

string fmt_t::operator()(init_t<string> strings) {
  const char* f = format;
  string result;

  for (auto& s : strings) {
    while (*f) {
      char current = f[0];
      char next    = f[1];

      if      (current == '%' && next == '%') { result +=     '%'; f += 2;        } 
      else if (current == '%'               ) { result +=       s; f += 1; break; }
      else                                    { result += current; f += 1;        }

      *f || rmr.die("fmt %: ran out of format string!");
    }
  }

  const char* trailing = f;

  while (*f) {
    char current = f[0];
    char next    = f[1];

    if      (current == '%' && next == '%') { f += 2;                                           } 
    else if (current == '%'               ) { rmr.die("fmt: unsubsituted %%: %"_fmt(trailing)); }

    f++;
  }

  return result += trailing;
}

fmt_t operator""_fmt(const char* b, size_t l) { return fmt_t(b); }
