#import <cstdint>
typedef int8_t        i8;
typedef int16_t       i16;
typedef int32_t       i32;
typedef int64_t       i64;
typedef uint8_t       u8;
typedef uint16_t      u16;
typedef uint32_t      u32;
typedef uint64_t      u64;
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef signed char   schar;
typedef wchar_t       wchar;
typedef intptr_t      iptr;
typedef uintptr_t     uptr;
typedef float         f32;
typedef double        f64;

#import <memory>
template<typename T> using unique_ptr = std::unique_ptr<T>;

#import <typeindex>
using std::type_index;

#import <string>
using std::string;
using std::u32string;

#import <sstream>
using std::stringstream;

#import <vector>
using std::vector;

#import <iostream>
using std::iostream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

#import <unordered_set>
using std::unordered_set;
template<typename T> using set = std::unordered_set<T>;

#import <unordered_map>
using std::unordered_map;
template<typename K, typename V> using map = std::unordered_map<K, V>;

#import <tuple>
using std::tuple;
using std::pair;

#import <list>
using std::list;

using namespace std::literals::string_literals;
using namespace std::literals::chrono_literals;

#import <regex>
using std::regex;
using std::regex_token_iterator;
using std::sregex_token_iterator;
using std::smatch;

template<typename T> using init_t = std::initializer_list<T>;
template<typename T> using fun_t  = std::function<T>;

using std::runtime_error;

struct cam_t;      struct event_t;    struct gl_t;
struct hints_t;    struct img_t;      struct key_e;
struct nav_t;      struct nothing_t;  struct render_e;
struct sym_t;      struct syphon_t;   struct target_t;
struct top_t;      struct view_t;     struct wall_t;
struct whatever_t; struct win_t;      struct window_t;
struct node_t;     struct gl_guard_t; struct target_t;
struct tick_e;     struct wave_t;     struct channel_t;

struct vec2;  struct vec3;  struct vec4;       
struct ivec2; struct ivec3; struct ivec4;       
struct uvec2; struct uvec3; struct uvec4;       
struct mat2;  struct mat3;  struct mat4;

template<class T> struct frame_t;

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#import "free.h"
