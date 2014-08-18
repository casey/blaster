#import "out.h"
#import "str.h"
#import "buf.h"
#import "seq.h"

#define SHOW(x) rmr << ("%: %"_fmt(#x, x))
#define DATA(TYPE, NAME) TYPE& NAME() { static TYPE _; return _; }

#define CLASS_NAME virtual const string& class_name() const {        \
  static string s{ rmr.get_class_name(__PRETTY_FUNCTION__) };  \
  return s;                                                    \
}

#define TOKEN_PASTE_INNER(a, b) a ## b
#define TOKEN_PASTE(a, b) TOKEN_PASTE_INNER(a, b)

struct population_t {
  population_t();
  ~population_t();
};

struct rmr_t : noncopyable_t {
  out_t operator<<(str_t);

  using _ = rmr_t&;

  static out_t  fatal();
  static out_t pretty();
  static out_t  null();

  static const string& ansi_red();
  static const string& ansi_green();
  static const string& ansi_clear();

  static size_t& heap_size();

  static double now();
  static double start();
  static double elapsed();
  static double elapsed(double);
  static u64    ms();
  static u64    us();
  static u64    ns();
  static u64    ms(double);
  static u64    us(double);
  static u64    ns(double);

  static string git_head();

  static char lower(char);
  static char upper(char);

  static string lower(const string&);
  static string upper(const string&);

  static string    rtrim     (const string& s);
  static string    trim      (const string& s);
  static string    ltrim     (const string& s);
  static bool      startswith(const string& haystack, const string& needle);
  static string    replace   (const string& original, const string& before, const string& after);
  static u32string codepoints(const string& s);

  static string get_class_name(const string& pretty_function);

  static double clamp(double n);
  static double clamp(double n, double min, double max);
  static double      round(double       x);
  static float       round(float        x);
  static long double round(long double  x);
  static double cos(double);
  static double tan(double);
  static double sin(double);
  static double asin(double);
  static double atan2(double y, double x);
  static double sqrt(double);

  static double t(double start, double end, double x);
  static bool   once(const sym_t& s);
  static bool   maybe();
  static bool   maybe(double p);
  static bool   rising_edge (bool a, bool b);
  static bool   falling_edge(bool a, bool b);
  static double angle(double a);
  static double posmod(double a, double p);

  static double random();
  static double random(double max);
  static double random(double min, double max);
  static int    random_int();
  static int    random_int(int max);
  static int    random_int(int min, int max);
  static double random_angle();
  static int    random_index(int count);

  static int stoi(const string& s);

  static string dirname (const string& path);
  static string basename(const string& path);
  static string realpath(const string& path);

  static _ atexit(void (*f)(void));

  static string  slurp(const char*   path);
  static string  slurp(const string& path);
  static string& fetch(const char*   path);
  static string& fetch(const string& path);
  static string& rsc  (const char*   path);
  static string& rsc  (const string& path);

  static _ dgram(const char* address, int port, const void* buffer, size_t size);
  static _ dgram(const char* address, int port, buf_t data);

  static string trace();
  [[noreturn]] static _ exec(char* path, char** argv);
  static string run(const char* cmd);
  static string run(const string& cmd);
  static string run(char* path, char** args, string input);
  static string run(const string& path, char** args, string input);
  static string run(const string& path, const seq_t<const string>& args, const string& input);

  static bool is_there(const string& path);
  static bool is_file (const string& path);
  static bool is_dir  (const string& path);

  static u32 hash(const void* data, size_t bytes);
  static u32 hash(buf_t);

  static string uuid(int length = 16);

  static _ hi();
  static _ error(str_t);
  static _ warn (str_t);
  static _ log  (str_t);
  static _ info (str_t);
  static _ spam (str_t);

  [[noreturn]] static _ iou();
  [[noreturn]] static _ banana();
  [[noreturn]] static _ die();
  [[noreturn]] static _ exit();
  [[noreturn]] static _ exit(int);
  [[noreturn]] static _ die(str_t);

  static int& loglevel();
  static _ loglevel(int);
  static _ sleep(double);

  static _ quiet();
  static _ verbose();

  static _ loglevel_error();
  static _ loglevel_warn();
  static _ loglevel_log();
  static _ loglevel_info();
  static _ loglevel_spam();

  static int& population();

  explicit operator bool() const;

  static int&  ti();
  static char& tc();

  static _ cfg(const sym_t&, const string&);
  static const string& cfg(const sym_t&);

  static const whatever_t& whatever();
  static const nothing_t&  nothing();

  ~rmr_t();

  template <typename T>
  static string join(const T& container, string sep) {
    string result;
    for (const string& s : container) {
      result += s;
      result += sep;
    }
    result.resize(result.length() - sep.length());
    return result;
  }

  template <typename T>
  static auto choice(const T& container) -> decltype(*container.begin()) {
    return *std::next(container.begin(), random_index(container.size()));
  }

  template <typename T>
  static double sum(const T& container) {
    double _ = 0;
    for (auto& x : container) {
      _ += x;
    }
    return _;
  }

  template <typename T>
  static double mean(const T& container) { return sum(container) / container.size(); }

  template<typename T, int size> constexpr static int size(T(&)[size]) { return size; }

  template<typename T> static const T& constant(      T& _) { return const_cast<const T&>(_); }
  template<typename T> static       T& variable(const T& _) { return const_cast<      T&>(_); }

  template<typename T> static bool changed(T& lvalue, const T& rvalue) {
    if (lvalue == rvalue) return false;
    lvalue = rvalue;
    return true;
  }

  static _ zero(void* p, size_t count);
  static _ zero(buf_t object);

  static wave_t& wave();

  constexpr static double tau() { return 6.283185307179586476925286766559005768394338798750211641949889184615632812; }
  constexpr static double pi () { return tau() / 2; }

  constexpr static u64 kb() { return u64(1) << 10; }
  constexpr static u64 mb() { return u64(1) << 20; }
  constexpr static u64 gb() { return u64(1) << 30; }
  constexpr static u64 tb() { return u64(1) << 40; }

  static string format_bytes(u64 bytes);

  template<typename T> constexpr T cmax(T a, T b) { return a < b ? b : a; }
  template<typename T, typename ... R> constexpr T cmax(T a, T b, R ... rest) { return cmax(cmax(a, b), rest...); }
  template<typename T> constexpr T cmin(T a, T b) { return a > b ? b : a; }
  template<typename T, typename ... R> constexpr T cmin(T a, T b, R ... rest) { return cmax(cmax(a, b), rest...); }
  static rmr_t& instance();
private:
  rmr_t();
};

extern rmr_t& rmr;

void    operator"" _error(const char* b, size_t l);
void    operator"" _warn (const char* b, size_t l);
void    operator"" _log  (const char* b, size_t l);
void    operator"" _info (const char* b, size_t l);
void    operator"" _spam (const char* b, size_t l);
void    operator"" _die  (const char* b, size_t l);
double  operator"" _t    (long double d          );
double  operator"" _t    (unsigned long long n   );
string& operator"" _rsc  (const char* b, size_t l);
regex   operator"" _re   (const char* b, size_t l);
