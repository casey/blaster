#import "rmr.h"
#import "str.h"
#import "fmt.h"
#import "sym.h"
#import "once.h"
#import "rec.h"
#import "wave.h"

#import <unistd.h>
#import <fstream>
#import <cmath>

rmr_t& rmr = rmr_t::instance();

static_assert(std::is_empty<rmr_t>::value, "rmr_t not empty");

using _ = rmr_t&;

rmr_t::rmr_t() {
  rmr.info("rmr: starting up");
  static int count = 0;
  if (count != 0) {
    fatal() << "More than 1 rmr_t instantiated!";
  }
  count++;
}

rmr_t::~rmr_t() {
  rmr.info("rmr: shutting down");
  rmr.info("rmr: heap size: %"_fmt(rmr.format_bytes(rmr.heap_size())));
  if (population() != 0) rmr << "rmr: population not zero:" << population();
}

_ rmr_t::instance() {
  static rmr_t _;
  return _;
}

out_t rmr_t::fatal() {
  return out_t().arm();
}

out_t rmr_t::pretty() {
  return out_t();
}

out_t rmr_t::null() {
  return out_t().off();
};

out_t rmr_t::operator<<(str_t _) { 
  return (out_t() << _.str());
}

_ log_helper(int level, str_t _) {
  if (rmr.loglevel() >= level) {
    cerr << _.str() << endl;
    cerr.flush();
  }
  return rmr;
}

_ rmr_t::error(str_t _) { return log_helper(-2, _); }
_ rmr_t::warn (str_t _) { return log_helper(-1, _); }
_ rmr_t::log  (str_t _) { return log_helper( 0, _); }
_ rmr_t::info (str_t _) { return log_helper(+1, _); }
_ rmr_t::spam (str_t _) { return log_helper(+2, _); }

_ rmr_t::quiet         () { return loglevel(-3); }
_ rmr_t::loglevel_error() { return loglevel(-2); }
_ rmr_t::loglevel_warn () { return loglevel(-1); }
_ rmr_t::loglevel_log  () { return loglevel( 0); }
_ rmr_t::loglevel_info () { return loglevel( 1); }
_ rmr_t::loglevel_spam () { return loglevel( 2); }
_ rmr_t::verbose       () { return loglevel( 3); }

rmr_t::operator bool() const {
  return true;
}

[[noreturn]] _ rmr_t::die() {
  die("rmr.die: dead!");
}

[[noreturn]] _ rmr_t::exit() {
  ::exit(0);
}

[[noreturn]] _ rmr_t::exit(int code) {
  ::exit(code);
}

[[noreturn]] _ rmr_t::die(str_t _) {
  log(trace());
  error(_);
  exit(1);
}

int& rmr_t::population() { static int p = 0; return p; };

population_t:: population_t() { rmr.population()++; }
population_t::~population_t() { rmr.population()--; }

int& rmr_t::loglevel()   { static int l = 0; return l; };
_ rmr_t::loglevel(int n) { loglevel() = n; return rmr; };

_ rmr_t::hi()  { log("hi"); return rmr; }
_ rmr_t::iou() { die("IOU: working code"); }

[[noreturn]] _ rmr_t::banana() { die("bananaphone: ring ring ring ring ring ring ring"); }

const string& rmr_t::ansi_red()   { static string s = "\033[1;31m"; return s; }
const string& rmr_t::ansi_green() { static string s = "\033[1;32m"; return s; }
const string& rmr_t::ansi_clear() { static string s = "\033[0m";    return s; }

double rmr_t::now() {
  auto t = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t).count() / 1e9;
}

double rmr_t::start() {
  static auto t = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t).count() / 1e9;
}

double rmr_t::elapsed() {
  return now() - start();
}

double rmr_t::elapsed(double t) {
  return t - start();
}

u64 rmr_t::ms() {
  auto t = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
}

u64 rmr_t::us() {
  auto t = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::microseconds>(t).count();
}

u64 rmr_t::ns() {
  auto t = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t).count();
}

u64 rmr_t::ms(double t) { return round(t * 1'000        ); }
u64 rmr_t::us(double t) { return round(t * 1'000'000    ); }
u64 rmr_t::ns(double t) { return round(t * 1'000'000'000); }

#import <execinfo.h>

string rmr_t::trace() {
  vector<string> frames;
  int max_frames = 100;
  void *array[max_frames];
  int trace_size = backtrace(array, max_frames);
  char **strings = backtrace_symbols(array, trace_size);
  for(int i = trace_size - 1; i >= 2; i--)
    frames.push_back(string(strings[i]));
  free(strings);

  string s;
  for(string frame: frames) {
    s += frame;
    s += "\n";
  }
  s.erase(s.length() - 1, 1);

  return s;
}

#import <sys/socket.h>
#import <arpa/inet.h>

_ rmr_t::dgram(const char* address, int port, const void* buffer, size_t count) {
  static int sock = -1;
  rmr.info("sending datagram");

  int ti;

  if (sock == -1) {
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    sock != -1 || rmr.die("dgram: couldn't open socket");
    ti = (1 << 16) - 1; setsockopt(sock, SOL_SOCKET, SO_SNDBUF,    &ti, sizeof(ti));
    ti = 1;             setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &ti, sizeof(ti));
  }

  struct sockaddr_in dest;
  rmr.zero(dest);
  dest.sin_family      = AF_INET;
  dest.sin_port        = htons(port);
  dest.sin_addr.s_addr = inet_addr(address);

  sendto(sock, buffer, count, 0, (struct sockaddr*)&dest, sizeof(dest));

  return rmr;
}

_ rmr_t::dgram(const char* address, int port, buf_t data) {
  return dgram(address, port, data.buffer(), data.size());
}

_ rmr_t::zero(buf_t object) {
  return zero(object.buffer(), object.size());
}

_ rmr_t::zero(void* p, size_t count) {
  memset(p, 0, count);
  return rmr;
}

wave_t& rmr_t::wave() {
  static wave_t _;
  return _;
}

[[noreturn]] _ rmr_t::exec(char* path, char** argv) {
  execv(path, argv);
  rmr.die("rmr.exec: survived exec!");
}

string rmr_t::run(const string& cmd) {
  return run(cmd.c_str());
}

string rmr_t::run(const char* cmd) {
  string result;
  FILE* pipe = popen(cmd, "r");
  if (!pipe) rmr.die("run: failed to open pipe: %"_fmt(cmd));
  char buffer[128];
  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  int status = pclose(pipe);
  if (status != 0) rmr.die("run: command failed: %"_fmt(status));
  return result;
}

string rmr_t::run(const string& path, const seq_t<const string>& args, const string& input) {
  vector<char*> argv;

  for (const string& s : args) {
    argv.push_back((char*)s.c_str());
  }
  argv.push_back(nullptr);

  return run((char*)path.c_str(), argv.data(), input);
};

string rmr_t::run(char* path, char** args, string input) {
  rmr.info("rmr.run: running: %"_fmt(path));
  for (int i = 0; args[i] != nullptr; i++) {
    rmr.info("argument %: \"%\""_fmt(i, args[i]));
  }
  rmr.info("input: %"_fmt(input));

  int pipe_in [2];
  int pipe_out[2];

  pipe(pipe_in ) && rmr.die("iopipe: error creating pipe_in" );
  pipe(pipe_out) && rmr.die("iopipe: error creating pipe_out");

  rmr.info("rmr.run: pipes created, forking...");

  pid_t pid = fork();

  pid == -1 && rmr.die("rmr.run: fork unsuccessful");

  if (pid == 0) { // child
    close(1);
    dup(pipe_out[1]);

    close(0);
    dup(pipe_in[0]);  

    close(pipe_out[0]);
    close(pipe_out[1]);
    close(pipe_in[0]);
    close(pipe_in[1]);
    rmr.exec(path, args);
  }

  rmr.info("rmr.run: parent: sending input to child");

  FILE* child_in  = fdopen(pipe_out[0], "r");
  FILE* child_out = fdopen(pipe_in[1], "w");
  close(pipe_out[1]);
  close(pipe_in[0]);

  fprintf(child_out, "%s", input.c_str());
  fflush(child_out);
  fclose(child_out);

  int result;
  wait(&result);

  rmr.info("rmr.run: parent: child process returned %"_fmt(result));

  string output("");

  char temp[1024];
  while (fgets(temp, 1024, child_in)) {
    output += temp;
  }

  return output;
}

#include <sys/stat.h>

bool rmr_t::is_dir  (const string& path) { struct stat s; return stat(path.c_str(), &s) == 0 && S_ISDIR(s.st_mode); }
bool rmr_t::is_file (const string& path) { struct stat s; return stat(path.c_str(), &s) == 0 && S_ISREG(s.st_mode); }
bool rmr_t::is_there(const string& path) { struct stat s; return stat(path.c_str(), &s);                            }

string rmr_t::git_head() {
  return trim(run("git --git-dir="s + cfg("base") + ".git rev-parse --short HEAD"));
}

string rmr_t::ltrim(const string& original) {
  string s = original;
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char c){return !std::isspace(c);}));
  return s;
}

char rmr_t::lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    c += 'a' - 'A';
  }
  return c;
}

char rmr_t::upper(char c) {
  if (c >= 'a' && c <= 'z') {
    c -= 'a' - 'A';
  }
  return c;
}

string rmr_t::lower(const string& original) {
  string copy = original;
  for (char& c : copy) c = lower(c);
  return copy;
}

string rmr_t::upper(const string& original) {
  string copy = original;
  for (char& c : copy) c = upper(c);
  return copy;
}

string rmr_t::rtrim(const string& original) {
  string s = original;
  s.erase(std::find_if(s.rbegin(), s.rend(), [](char c){return !std::isspace(c);}).base(), s.end());
  return s;
}

string rmr_t::trim(const string& original) {
  return ltrim(rtrim(original));
}

bool rmr_t::startswith(const string& haystack, const string& needle) {
  return haystack.compare(0, needle.length(), needle) == 0;
}

string rmr_t::replace(const string& original, const string& before, const string& after) {
    std::string retval;
    std::string::const_iterator end     = original.end();
    std::string::const_iterator current = original.begin();
    std::string::const_iterator next    =
            std::search( current, end, before.begin(), before.end() );
    while ( next != end ) {
        retval.append( current, next );
        retval.append( after );
        current = next + before.size();
        next = std::search( current, end, before.begin(), before.end() );
    }
    retval.append( current, next );
    return retval;
}

#import <codecvt>

u32string rmr_t::codepoints(const string& s) {
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
  return converter.from_bytes(s.data());
}

string rmr_t::get_class_name(const string& pretty_function) {
  size_t colons = pretty_function.find("::");
  if (colons == std::string::npos) return "::";
  size_t begin = pretty_function.substr(0, colons).rfind(" ") + 2;
  size_t end = colons - begin;
  return pretty_function.substr(begin, end);
}

double      rmr_t::clamp(double n)                         { return clamp(n, 0.0, 1.0);                }
double      rmr_t::clamp(double n, double min, double max) { return n < min ? min : n > max ? max : n; }
double      rmr_t::round(double       x)                   { return std::round(x);                     }
float       rmr_t::round(float        x)                   { return std::round(x);                     }
long double rmr_t::round(long double  x)                   { return std::round(x);                     }

double rmr_t::cos (double x) { return std::cos (x); }
double rmr_t::tan (double x) { return std::tan (x); }
double rmr_t::sin (double x) { return std::sin (x); }
double rmr_t::asin(double x) { return std::asin(x); }
double rmr_t::atan2(double y, double x) { return std::atan2(y, x); }
double rmr_t::sqrt(double x) { return std::sqrt(x); }

double rmr_t::t(double start, double end, double x) {
  return x <= start ? 0.0 :
         x >= end   ? 1.0 :
                      1.0 - ((end - x) / (end - start));
}

bool rmr_t::once(const sym_t& s) {
  static map<sym_t, bool> table;
  if (table.count(s) > 0) return false;
  table[s] = true;
  return true;
}

bool rmr_t::maybe() {
  return maybe(0.5);
}

bool rmr_t::maybe(double p) {
  return rmr.random() < p;
}

bool rmr_t::rising_edge (bool a, bool b) { return !a &&  b; }
bool rmr_t::falling_edge(bool a, bool b) { return  a && !b; }

double rmr_t::angle(double a) {
  return posmod(a, rmr.tau());
}

double rmr_t::posmod(double a, double p) {
  a = std::fmod(a, p);
  return a < 0 ? a + p : a;
}

#import <random>

std::default_random_engine& rng() {
  static std::default_random_engine engine;
  static once_t once;

  if (once) {
    double now = rmr.now();
    u64    u   = *(u64*)&now;
    u32    t   = u >> 32;
    u32    b   = u;
    engine.seed(t ^ b);
  }

  return engine;
}

double rmr_t::random(double min, double max) {
  return std::uniform_real_distribution<double>(min, max)(rng());
}

double rmr_t::random() {
  return std::uniform_real_distribution<double>(0.0, 1.0)(rng());
}

double rmr_t::random(double max) {
  return random(0.0, max);
}

double rmr_t::random_angle() {
  return random(0.0, rmr.tau());
}

int rmr_t::random_int() {
  return random_int(0, INT_MAX);
}

int rmr_t::random_int(int max) {
  return random_int(0, max);
}

int rmr_t::random_int(int min, int max) {
  return std::uniform_int_distribution<int>(min, max)(rng());
}

int rmr_t::random_index(int count) {
  count <= 0 && rmr.die("rmr.random_index: bad count: %"_fmt(count));
  return random_int(0, count - 1);
}

#import <libgen.h>
#import <string.h>
#import <stdlib.h>

string rmr_t::dirname(const string& path) {
  auto z = strdup(path.c_str());
  string result = ::dirname(z);
  free(z);
  return result;
}

string rmr_t::basename(const string& path) {
  auto z = strdup(path.c_str());
  string result = ::basename(z);
  free(z);
  return result;
}

string rmr_t::realpath(const string& s) {
  char* z = ::realpath(s.c_str(), nullptr);
  string result = string(z);
  free(z);
  return result;
}

_ rmr_t::atexit(void (*f)(void)) {
  auto result = ::atexit(f);
  result == 0 || rmr.die("rmr.atexit: failed with result code %"_fmt(result));
  return rmr;
}

int rmr_t::stoi(const string& s) {
  size_t i = 0;
  int    n = std::stoi(s, &i, 10);
  i != s.length() && rmr.die("rmr.stoi: extra characters in string: %"_fmt(s));
  return n;
}

void MurmurHash3_x86_32  (const void * key, int len, uint32_t seed, void * out);
void MurmurHash3_x86_128 (const void * key, int len, uint32_t seed, void * out);
void MurmurHash3_x64_128 (const void * key, int len, uint32_t seed, void * out);

u32 rmr_t::hash(const void* data, size_t bytes) {
  u32 out;
  MurmurHash3_x86_32(data, bytes, 0, &out);
  return out;
}

u32 rmr_t::hash(buf_t data) {
  return hash(data.buffer(), data.size());
}

string rmr_t::uuid(int length) {
  static string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string s;

  for (int i = 0; i < length; i++) {
    s.push_back(choice(characters));
  }

  return s;
}

string rmr_t::slurp(const char* path) {
  std::ifstream in(path, std::ios::in | std::ios::binary);
  if (!in) rmr.fatal() << "rmr.slurp: failed:" << path << "errno:" << errno;
  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();
  return(contents);
}

string rmr_t::slurp(const string& path) {
  return slurp(path.c_str());
}

string& rmr_t::fetch(const string& path) {
  return fetch(path.c_str());
}

string& rmr_t::fetch(const char*   path) {
  static map<string, string> cache;
  
  if (!cache.count(path)) {
    rmr.spam("fetch: cache miss: "s + path);
    cache[path] = slurp(path);
  }

  return cache[path];
}

string& rmr_t::rsc(const char*   path) {
  auto s = "rsc/"s + path; return fetch(s.c_str());
}

string& rmr_t::rsc(const string& path) {
  return rsc(path.c_str());
}

_ rmr_t::sleep(double t) {
  usleep(useconds_t(t * 1000 * 1000));
  return rmr;
}

map<sym_t, string>& cfg_table() {
  static map<sym_t, string> table;
  return table;
}

_ rmr_t::cfg(const sym_t& key, const string& value) {
  if (cfg_table().count(key)) rmr.fatal() << "rmr.cfg: duplicate set:" << key;
  cfg_table()[key] = value;
  return rmr;
}

const string& rmr_t::cfg(const sym_t& key) {
  cfg_table().count(key) || rmr.fatal() << "rmr.cfg: reading unset key:" << key;
  return cfg_table()[key];
}

const whatever_t& rmr_t::whatever() { static whatever_t x; return x; }
const  nothing_t& rmr_t:: nothing() { static  nothing_t x; return x; }


int&  rmr_t::ti() { static int  _ = 0; return _; }
char& rmr_t::tc() { static char _ = 0; return _; }

string rmr_t::format_bytes(u64 count) {
  double result = (double)count;

  int i = 0;
  while (result > 1024) {
    result /= 1024;
    i++;
  }

  const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
  size_t unit_count = rmr.size(units);

  i < unit_count || rmr.die("rmr.format_bytes: can't format bytes: %"_fmt(count));

  return "%"_fmt((u64)result) + string(units[i]);
}

size_t& rmr_t::heap_size() {
  static size_t _;
  return _;
}

#import <malloc/malloc.h>

void * operator new(std::size_t n) {
  void* p = malloc(n);
  if (p) rmr_t::heap_size() += malloc_size(p);
  return p;
}

void operator delete(void * p) throw() {
  if (p) rmr_t::heap_size() -= malloc_size(p);
  free(p);
}

void    operator"" _error(const char* b, size_t l) { rmr.error(string(b, l));      }
void    operator"" _warn (const char* b, size_t l) { rmr.warn (string(b, l));      }
void    operator"" _log  (const char* b, size_t l) { rmr.log  (string(b, l));      }
void    operator"" _info (const char* b, size_t l) { rmr.info (string(b, l));      }
void    operator"" _spam (const char* b, size_t l) { rmr.spam (string(b, l));      }
void    operator"" _die  (const char* b, size_t l) { rmr.die  (string(b, l));      }
double  operator"" _t    (long double d          ) { return d * rmr.tau();         }
double  operator"" _t    (unsigned long long n   ) { return n * rmr.tau();         }
string& operator"" _rsc  (const char* b, size_t l) { return rmr.rsc(string(b, l)); }
regex   operator"" _re   (const char* b, size_t l) { return regex(string(b, l));   }

static_assert(CHAR_BIT == 8, "We are totally fucked.");

#define _(a, b) static_assert(std::is_same<a, b>::value, "type " #a " is not " #b)
_(int,          i32);
_(unsigned int, u32);
_(short       , i16);
_(unsigned short, u16);
_(unsigned long long int, u64);
#undef _
