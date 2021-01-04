#import "gl.h"
#import "sym.h"
#import "rmr.h"
#import "fmt.h"
#import "vec.h"
#import "window.h"

#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

template <uint E>
int gl_get_i() {
  int x;
  glGetIntegerv(E, &x);
  return x;
}

template <uint E>
int gl_get_program_i(uint p) {
  int x;
  glGetProgramiv(p, E, &x);
  return x;
}

template <uint E>
int gl_get_shader_i(uint s) {
  int x;
  glGetShaderiv(s, E, &x);
  return x;
}

template<uint E> struct grs { typedef void type; };
template<uint E> struct grp { typedef void type; };
template<uint E> struct grg { typedef void type; };

template<uint E> typename grp<E>::type gl_get_program(uint p);
template<uint E> typename grs<E>::type gl_get_shader (uint s);
template<uint E> typename grg<E>::type gl_get        (      );

template<> struct grg<GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS> { typedef int type; };
template<> int gl_get<GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS>() { return gl_get_i<GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS>(); }

template<> struct grp<GL_ACTIVE_ATTRIBUTES> { typedef int type; };
template<> int gl_get_program<GL_ACTIVE_ATTRIBUTES>(uint p) { return gl_get_program_i<GL_ACTIVE_ATTRIBUTES>(p); }

template<> struct grp<GL_ACTIVE_UNIFORMS> { typedef int type; };
template<> int gl_get_program<GL_ACTIVE_UNIFORMS>(uint p) { return gl_get_program_i<GL_ACTIVE_UNIFORMS>(p); }

template<> struct grp<GL_LINK_STATUS> { typedef int type; };
template<> int gl_get_program<GL_LINK_STATUS>(uint p) { return gl_get_program_i<GL_LINK_STATUS>(p); }

template<> struct grp<GL_VALIDATE_STATUS> { typedef int type; };
template<> int gl_get_program<GL_VALIDATE_STATUS>(uint p) { return gl_get_program_i<GL_VALIDATE_STATUS>(p); }

template<> struct grp<GL_ATTACHED_SHADERS> { typedef int type; };
template<> int gl_get_program<GL_ATTACHED_SHADERS>(uint p) { return gl_get_program_i<GL_ATTACHED_SHADERS>(p); }

template<> struct grp<GL_INFO_LOG_LENGTH> { typedef int type; };
template<> int gl_get_program<GL_INFO_LOG_LENGTH>(uint p) { return gl_get_program_i<GL_INFO_LOG_LENGTH>(p); }

template<> struct grs<GL_COMPILE_STATUS> { typedef int type; };
template<> int gl_get_shader<GL_COMPILE_STATUS>(uint s) { return gl_get_shader_i<GL_COMPILE_STATUS>(s); }

template<> struct grs<GL_INFO_LOG_LENGTH> { typedef int type; };
template<> int gl_get_shader<GL_INFO_LOG_LENGTH>(uint s) { return gl_get_shader_i<GL_INFO_LOG_LENGTH>(s); }

static constexpr int last_mode() {
  return rmr.cmax(
    GL_POINTS
  , GL_LINES
  , GL_TRIANGLES
  , GL_LINE_LOOP
  , GL_LINE_STRIP
  , GL_TRIANGLE_STRIP
  , GL_TRIANGLE_FAN);
}

struct var_t {
  bool  ready = false;
  sym_t name = "";
  bool  attrib;
  int   index;
  int   location;
  int   size;
  uint  type;

  var_t(sym_t name, bool attrib, int index, int location, int size, uint type)
  : name(name), attrib(attrib), index(index), location(location), size(size), type(type)
  { }

  var_t() {
    rmr.die("var_t: default constructor is forbidden");
  }

  void check(int size, int type) {
    this->size == size || rmr.die("var.check: unexpected variable size: %: %"_fmt(name, size));
    this->type == type || rmr.die("var.check: unexpected variable type: %: %"_fmt(name, type));
  }

  static var_t get_attrib(uint p, uint i) {
    int size;
    uint type;
    char name[513];
    glGetActiveAttrib(p, i, 512, nullptr, &size, &type, name);
    int location = glGetAttribLocation(p, name);
    return {name, true, (int)i, location, size, type};
  }

  static var_t get_uniform(uint p, uint i) {
    int size;
    uint type;
    char name[513];
    glGetActiveUniform(p, i, 512, nullptr, &size, &type, name);
    int location = glGetUniformLocation(p, name);
    return {name, false, (int)i, location, size, type};
  }
};

struct gl_t::data_t {
  data_t(window_t& w) : w(w) {}

  bool     is_inactive () { return state == 0;                                                   }
  bool     is_preparing() { return state == 1;                                                   }
  bool     is_drawing  () { return state == 2;                                                   }
  void assert_inactive () { is_inactive () || rmr.die("gl_t: out of phase: expected inactive" ); }
  void assert_preparing() { is_preparing() || rmr.die("gl_t: out of phase: expected preparing"); }
  void assert_drawing  () { is_drawing  () || rmr.die("gl_t: out of phase: expected drawing"  ); }
  void  start_inactive () { assert_drawing  (); state = 0;                                       }
  void  start_preparing() { assert_inactive (); state = 1;                                       }
  void  start_drawing  () { assert_preparing(); state = 2;                                       }

  var_t& get_var(sym_t s) {
    try {
      return vars.at(current_program).at(s);
    } catch(std::out_of_range& e) {
      rmr.die("gl.get_var: disaster: % / %"_fmt(current_program, s));
    }
  }

  template<typename T>
  using map_member_t = map<sym_t, T> data_t::*;

  template<typename T>
  const T& lookup(map_member_t<T> mp, sym_t key) {
    auto current = this;

    while (current) {
      auto& m = current->*mp;
      auto  i = m.find(key);
      if (i != m.end()) return i->second;
      current = current->parent;
    }

    rmr.die("gl.lookup: couldn't find %"_fmt(key));
  }

  window_t&                     w;
  data_t*                       parent            = nullptr;
  loader_t                      loader            = {};
  postprocessor_t               postprocessor     = {};
  vector<gl_t*>                 children          = {};
  map<sym_t, u32>               vbos              = {};
  map<sym_t, u32>               vaos              = {};
  map<sym_t, u32>               fbos              = {};
  map<sym_t, u32>               rbos              = {};
  map<sym_t, u32>               prgs              = {};
  map<sym_t, bool>              prgs_to_reload    = {};
  map<sym_t, u32>               texs              = {};
  map<sym_t, map<sym_t, var_t>> vars              = {};
  map<sym_t, u64>               vbo_sizes         = {};
  map<sym_t, gl_t::supplier_t>  suppliers         = {};
  int                           mode              = -1;
  int                           state             =  0;
  u64                           drawable_vertices =  0;
  sym_t                         current_program   = {};
  population_t                  pop               = {};
};

using _ = gl_t::_;

gl_t::gl_t(window_t& w) : __(*new data_t(w)) {
  new_vao("");
  bind_vao("");
  glEnable(GL_SCISSOR_TEST);
  glEnablei(GL_BLEND, 0);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_PROGRAM_POINT_SIZE);
}

void delete_objects(map<sym_t, u32>& m, u8(*is)(uint), void(*del)(int, const uint*), const char* msg) {
  for (auto _ : m) {
    is(_.second) || rmr.die("%: %"_fmt(msg, _.first));
    del(1, &_.second);
  }
  m.clear();
}

gl_t::~gl_t() {
  for (auto child : __.children) {
    delete child;
  }

  for (auto _ : __.prgs) {
    auto p = _.second;
    int shader_count = gl_get_program<GL_ATTACHED_SHADERS>(p);
    u32 shaders[shader_count];
    glGetAttachedShaders(p, shader_count, nullptr, shaders);
    for (auto s : shaders) glDeleteShader(s);
    glDeleteProgram(p);
  }

  __.prgs.clear();

  delete_objects(__.vbos, glIsBuffer,       glDeleteBuffers      , "~gl: bad vbo");
  delete_objects(__.texs, glIsTexture,      glDeleteTextures     , "~gl: bad tex");
  delete_objects(__.vaos, glIsVertexArray,  glDeleteVertexArrays , "~gl: bad vao");
  delete_objects(__.fbos, glIsFramebuffer,  glDeleteFramebuffers , "~gl: bad fbo");
  delete_objects(__.rbos, glIsRenderbuffer, glDeleteRenderbuffers, "~gl: bad rbo");

  delete &__;
}

_ gl_t::spawn() {
  auto child = new gl_t(__.w);
  child->__.parent = &this->__;
  __.children.push_back(child);
  return *child;
}

_ gl_t::reload_prgs() {
  __.assert_inactive();
  for (auto item : __.prgs) __.prgs_to_reload[item.first] = true;
  for (auto child : __.children) child->reload_prgs();
  return *this;
}

_ gl_t::prepare(sym_t program) {
  auto i = __.prgs.find(program);

  if (i == __.prgs.end() || __.prgs_to_reload[program]) {
    rmr.info("gl.prepare: new program: %"_fmt % program);
    new_prg(program);
    i = __.prgs.find(program);
  }

  auto p = i->second;

  __.start_preparing();
  glUseProgram(p);

  __.current_program   = program;
  __.mode              = -1;
  __.drawable_vertices = std::numeric_limits<decltype(__.drawable_vertices)>::max();
  for (auto& item : __.vars[program]) {
    auto& var = item.second;
    var.ready = false;
  }
  return *this;
}

_ gl_t::ready() {
  __.start_drawing();
  for (auto& item : __.vars[__.current_program]) {
    auto& sym = item.first;
    auto& var = item.second;

    if (var.ready) continue;
    __.lookup(&gl_t::data_t::suppliers, sym)(*this, sym);
    var.ready || rmr.die("variable % not ready (supplier failed)"_fmt % sym);
  }
  return *this;
}

_ gl_t::done() {
  if (__.is_preparing()) rmr.die("gl_t.swap: out of phase: preparing but should be inactive or drawing");
  if (__.is_drawing()) __.start_inactive();
  return *this;
}

_ gl_t::pack(init_t<sym_t> attributes, sym_t vbo) {
  glBindBuffer(GL_ARRAY_BUFFER, get_vbo(vbo));
  auto stride = attributes.size() * 4 * sizeof(float);
  size_t first = 0;
  u64 count = std::floor(double(__.vbo_sizes[vbo]) / stride);
  __.drawable_vertices = std::min(__.drawable_vertices, count);

  auto &vars = __.vars[__.current_program];
  for (auto a : attributes) {
    auto& var = vars[a];
    glVertexAttribPointer(var.location, 4, GL_FLOAT, false, stride, ((char*)0) + first);
    glEnableVertexAttribArray(var.location);
    first += 4 * sizeof(float);
    var.ready = true;
  }

  return *this;
}

_ gl_t::value(sym_t s, sym_t t) {
  auto& var = __.get_var(s);
  var.check(1, GL_SAMPLER_2D);
  if (var.attrib) rmr.die("gl.value: sampler attributes are not a thing");

  auto p = get_prg(__.current_program);

  u32 name = __.lookup(&gl_t::data_t::texs, t);
  i32 unit;
  glGetUniformiv(p, var.location, &unit);

  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, name);

  var.ready = true;

  return *this;
}

_ gl_t::value(sym_t s, int a) {
  auto& var = __.get_var(s);
  var.check(1, GL_INT);
  if (var.attrib) rmr.die("gl.value: int attributes are not supported");
  else            glUniform1i(var.location, a);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, size_t a) {
  auto& var = __.get_var(s);
  var.check(1, GL_UNSIGNED_INT);
  if (var.attrib) rmr.die("gl.value: int attributes are not supported");
  else            glUniform1ui(var.location, a);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, double a) {
  auto& var = __.get_var(s);
  var.check(1, GL_FLOAT);
  if (var.attrib) glVertexAttrib1f(var.location, a);
  else            glUniform1f(var.location, a);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, const vec2& v) {
  return value(s, v.x(), v.y());
}

_ gl_t::value(sym_t s, double a, double b) {
  auto& var = __.get_var(s);
  var.check(1, GL_FLOAT_VEC2);
  if (var.attrib) glVertexAttrib2f(var.location, a, b);
  else            glUniform2f(var.location, a, b);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, const vec3& v) {
  return value(s, v.x(), v.y(), v.z());
}

_ gl_t::value(sym_t s, double a, double b, double c) {
  auto& var = __.get_var(s);
  var.check(1, GL_FLOAT_VEC3);
  if (var.attrib) glVertexAttrib3f(var.location, a, b, c);
  else            glUniform3f(var.location, a, b, c);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, const vec4& v) {
  return value(s, v.x(), v.y(), v.z(), v.w());
}

_ gl_t::value(sym_t s, double a, double b, double c, double d) {
  auto& var = __.get_var(s);
  var.check(1, GL_FLOAT_VEC4);
  if (var.attrib) glVertexAttrib4f(var.location, a, b, c, d);
  else            glUniform4f(var.location, a, b, c, d);
  var.ready = true;
  return *this;
}

_ gl_t::value(sym_t s, const mat4& m) {
  auto& var = __.get_var(s);
  var.check(1, GL_FLOAT_MAT4);
  if (var.attrib) rmr.die("gl.value: matrix vertex attributes not supported");
  else            glUniformMatrix4fv(var.location, 1, false, (const float*)&m);
  var.ready = true;
  return *this;
}

_ gl_t::loader(loader_t f) {
  __.loader && rmr.die("gl: duplicate loader");
  __.loader = f;
  return *this;
}

_ gl_t::postprocessor(postprocessor_t f) {
  __.postprocessor && rmr.die("gl: duplicate postprocessor");
  __.postprocessor = f;
  return *this;
}

_ gl_t::supplier(sym_t s, supplier_t f) {
  if (__.suppliers.count(s)) rmr.die("gl.supplier: duplicate supplier: %"_fmt(s));
  __.suppliers[s] = f;
  return *this;
}

_ gl_t::triangles () { __.mode = GL_TRIANGLES ; return *this; };
_ gl_t::points    () { __.mode = GL_POINTS    ; return *this; };
_ gl_t::lines     () { __.mode = GL_LINES     ; return *this; };
_ gl_t::line_strip() { __.mode = GL_LINE_STRIP; return *this; };

template<typename T>
bool is_max(T x) {
  return x == std::numeric_limits<T>::max();
}

_ gl_t::draw_arrays() {
  if (is_max(__.drawable_vertices)) {
    rmr.die("gl_t.draw_arrays: drawable vertices is at max, probably wrong");
  }

  draw_arrays(0, __.drawable_vertices);
  return *this;
}

_ gl_t::draw_arrays(int first, int count) {
  (__.mode >= 0 && __.mode <= last_mode()) || rmr.die("gl_t: draw_arrays: mode unset: %"_fmt % __.mode);

  if ((first + count) > __.drawable_vertices) {
    rmr.die("gl.draw_arrays: trying to draw too many vertices");
  }

  glDrawArrays(__.mode, first, count);
  return *this;
}

_ gl_t::new_tex(sym_t s, uint& dest) { new_tex(s); dest = get_tex(s); return *this; }
_ gl_t::new_prg(sym_t s, uint& dest) { new_prg(s); dest = get_prg(s); return *this; }
_ gl_t::new_vbo(sym_t s, uint& dest) { new_vbo(s); dest = get_vbo(s); return *this; }
_ gl_t::new_fbo(sym_t s, uint& dest) { new_fbo(s); dest = get_fbo(s); return *this; }
_ gl_t::new_rbo(sym_t s, uint& dest) { new_rbo(s); dest = get_rbo(s); return *this; }
_ gl_t::new_vao(sym_t s, uint& dest) { new_vao(s); dest = get_vao(s); return *this; }

_ gl_t::new_tex(sym_t s) {
  has_tex(s) && rmr.die("gl_t.new_tex: tex already exists: %"_fmt % s);
  glGenTextures(1, &__.texs[s]);

  __.assert_inactive();
  glBindTexture(GL_TEXTURE_2D, get_tex(s));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  return *this;
}

_ gl_t::new_fbo(sym_t s) {
  has_fbo(s) && rmr.die("gl_t.new_fbo: already exists: %"_fmt % s);
  glGenFramebuffers(1, &__.fbos[s]);
  return *this;
}

_ gl_t::bind_fbo(sym_t s) {
  uint fbo = get_fbo(s);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  return *this;
}

_ gl_t::new_rbo(sym_t s) {
  has_rbo(s) && rmr.die("gl_t.new_rbo: already exists: %"_fmt % s);
  glGenRenderbuffers(1, &__.rbos[s]);
  return *this;
}

_ gl_t::bind_rbo(sym_t s) {
  uint rbo = get_rbo(s);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  return *this;
}

_ gl_t::new_vbo(sym_t s) {
  has_vbo(s) && rmr.die("gl_t.new_vbo: vbo already exists: %"_fmt % s);
  glGenBuffers(1, &__.vbos[s]);
  __.vbo_sizes[s] = 0;
  return *this;
}

_ gl_t::new_vao(sym_t s) {
  has_vao(s) && rmr.die("gl_t.new_vao: duplicate: %"_fmt % s);
  glGenVertexArrays(1, &__.vaos[s]);
  return *this;
}

_ gl_t::bind_vao(sym_t s) {
  has_vao(s) || rmr.die("gl_t.bind_vao: missing: %"_fmt % s);
  glBindVertexArray(__.vaos[s]);
  return *this;
}

uint gl_t::get_vbo(sym_t s) {
  auto i = __.vbos.find(s);
  i == __.vbos.end() && rmr.die("gl.get_vbo: vbo does not exist: %"_fmt % s);
  return i->second;
}

uint gl_t::get_prg(sym_t s) {
  auto i = __.prgs.find(s);
  i == __.prgs.end() && rmr.die("gl.get_prg: prg does not exist: %"_fmt % s);
  return i->second;
}

uint gl_t::get_vao(sym_t s) {
  auto i = __.vaos.find(s);
  i == __.vaos.end() && rmr.die("gl.get_vao: vao does not exist: %"_fmt % s);
  return i->second;
}

uint gl_t::get_tex(sym_t s) {
  auto i = __.texs.find(s);
  i == __.texs.end() && rmr.die("gl.get_tex: tex does not exist: %"_fmt % s);
  return i->second;
}

uint gl_t::get_fbo(sym_t s) {
  auto i = __.fbos.find(s);
  i == __.fbos.end() && rmr.die("gl.get_fbo: does not exist: %"_fmt % s);
  return i->second;
}

uint gl_t::get_rbo(sym_t s) {
  auto i = __.rbos.find(s);
  i == __.rbos.end() && rmr.die("gl.get_rbo: does not exist: %"_fmt % s);
  return i->second;
}

bool gl_t::has_vbo(sym_t s) { return __.vbos.count(s); }
bool gl_t::has_prg(sym_t s) { return __.prgs.count(s); }
bool gl_t::has_vao(sym_t s) { return __.vaos.count(s); }
bool gl_t::has_tex(sym_t s) { return __.texs.count(s); }
bool gl_t::has_rbo(sym_t s) { return __.rbos.count(s); }
bool gl_t::has_fbo(sym_t s) { return __.fbos.count(s); }

_ gl_t::upload_ccw_quad(sym_t s) {
  static float ccw_quad[] = {1, -1, 0, 1, 1, 1, 0, 1, -1, 1, 0, 1, -1, 1, 0, 1, -1, -1, 0, 1, 1, -1, 0, 1};
  return buffer_data_static(s, sizeof(ccw_quad), ccw_quad);
}

_ gl_t::clear_color  (float r, float g, float b, float a) { glClearColor(r, g, b, a); return *this; }
_ gl_t::clear_color  (const vec4& v                     ) { return clear_color(v.r(), v.g(), v.b(), v.a()); }
_ gl_t::clear_depth  (float d                           ) { glClearDepth(d         ); return *this; }
_ gl_t::clear_stencil(float s                           ) { glClearDepth(s         ); return *this; }
_ gl_t::clear        (                                  ) { return clear(1, 1, 1);                  }

_ gl_t::point_size(float x) { glPointSize(x); return *this; }

_ gl_t::clear(bool color, bool depth, bool stencil) {
  int clear_bits = 0;
  if (color  ) clear_bits |=   GL_COLOR_BUFFER_BIT;
  if (depth  ) clear_bits |=   GL_DEPTH_BUFFER_BIT;
  if (stencil) clear_bits |= GL_STENCIL_BUFFER_BIT;

  if (clear_bits) glClear(clear_bits);
  return *this;
}

_ gl_t::aperture(int x, int y, int w, int h) {
  glViewport(x, y, w, h);
  glScissor(x, y, w, h);
  return *this;
}

_ gl_t::buffer_data_static(sym_t s, size_t bytes, const void* data) {
  glBindBuffer(GL_ARRAY_BUFFER, get_vbo(s));
  glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
  __.vbo_sizes[s] = bytes;
  return *this;
}

_ gl_t::buffer_data_dynamic(sym_t s, size_t bytes, const void* data) {
  glBindBuffer(GL_ARRAY_BUFFER, get_vbo(s));
  glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_DYNAMIC_DRAW);
  __.vbo_sizes[s] = bytes;
  return *this;
}

_ gl_t::buffer_sub_data(sym_t vbo, int offset, int size, void* data) {
  glBindBuffer(GL_ARRAY_BUFFER, get_vbo(vbo));
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
  return *this;
}

_ gl_t::image(sym_t texture, const img_t& data) {
  auto tex = get_tex(texture);
  __.assert_inactive();
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width(), data.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.bytes());
  return *this;
}

_ gl_t::image(sym_t texture, size_t width, size_t height) {
  auto tex = get_tex(texture);
  __.assert_inactive();
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  return *this;
}

_ gl_t::image(sym_t texture, const uvec2& size) {
  return image(texture, size.x(), size.y());
}

void expect_error(uint expected) {
  auto e = glGetError();
  e == expected || rmr.fatal() << "gl: expected % but got %"_fmt(gl_t::enum_name(expected), gl_t::enum_name(e));
}

_ gl_t::check()                    { expect_error(GL_NO_ERROR);          return *this; }
_ gl_t::expect_invalid_operation() { expect_error(GL_INVALID_OPERATION); return *this; }

struct prg_exception : runtime_error {
  prg_exception() : runtime_error("") {}
};

gl_t& gl_t::new_prg(sym_t s) {
  bool exists = has_prg(s);
  bool reloading = (exists && __.prgs_to_reload[s]);
  (exists && !reloading) && rmr.die("gl_t.new_prg: duplicate: %"_fmt % s);
  (exists && reloading) && rmr.info("gl.new_prg: reloading: %"_fmt(s));

  __.prgs_to_reload[s] = false;

  auto p = glCreateProgram();

  auto fail = [&](const string& msg){
    rmr << msg;
    reloading || rmr.exit(1);

    int shader_count = gl_get_program<GL_ATTACHED_SHADERS>(p);
    u32 shaders[shader_count];
    glGetAttachedShaders(p, shader_count, nullptr, shaders);
    for (auto s : shaders) glDeleteShader(s);
    glDeleteProgram(p);

    throw prg_exception();
    return true;
  };

  try {
    string prg_name = s;
    string src = __.loader ? __.loader(s) : load(s);

    vector<string> vs_lines;
    vector<string> fs_lines;

    enum class section_t { shared, vertex, fragment };
    auto section = section_t::shared;

    auto newline_re   = "\n|\r\n|\n\r|\r"_re;
    auto directive_re = "^//!(\\S+)\\s*$"_re;

    sregex_token_iterator iter(src.begin(), src.end(), newline_re, -1);
    sregex_token_iterator end;

    for (; iter != end; ++iter) {
      string line(*iter);
      std::smatch match;
      if (regex_match(line, match, directive_re)) {
        string directive = match[1];
        if (directive == "vertex") {
          section = section_t::vertex;
        } else if (directive == "fragment") {
          section = section_t::fragment;
        } else {
          fail("unrecognized shader directive"s + directive);
        }
      }

      switch (section) {
        case section_t::  shared: vs_lines.push_back(line); fs_lines.push_back(line); break;
        case section_t::  vertex: vs_lines.push_back(line); fs_lines.push_back(""  ); break;
        case section_t::fragment: vs_lines.push_back(""  ); fs_lines.push_back(line); break;
      }
    }

    auto common_src = rmr.slurp(rmr.cfg("base") + "common.glsl");
    glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, "/common.glsl", -1, common_src.c_str());

    auto shader = [&](string& src, uint type){
      auto c_str = src.c_str();
      auto s = glCreateShader(type);
      glAttachShader(p, s);

      glShaderSource(s, 1, &c_str, nullptr);
      auto path = "/.";
      glCompileShaderIncludeARB(s, 1, &path, nullptr);
      if (!gl_get_shader<GL_COMPILE_STATUS>(s)) {
        int l = gl_get_shader<GL_INFO_LOG_LENGTH>(s);
        char* log = new char[l];
        glGetShaderInfoLog(s, l, &l, log);
        fail("gl.new_prg: compilation error: %: %"_fmt(s, log));
      }
    };

    auto vs = rmr.join(vs_lines, "\n");
    auto fs = rmr.join(fs_lines, "\n");
    shader(vs, GL_VERTEX_SHADER);
    shader(fs, GL_FRAGMENT_SHADER);

    auto link_and_validate = [&](){
      glLinkProgram(p);

      if (!gl_get_program<GL_LINK_STATUS>(p)) {
        int l = gl_get_program<GL_INFO_LOG_LENGTH>(p);
        char* log = new char[l];
        glGetProgramInfoLog(p, l, &l, log);
        fail("bad link: %\n"_fmt(log));
      }

      glValidateProgram(p);
      if (!gl_get_program<GL_VALIDATE_STATUS>(p)) {
        int l = gl_get_program<GL_INFO_LOG_LENGTH>(p);
        char* log = new char[l];
        glGetProgramInfoLog(p, l, &l, log);
        fail("validation error: %\n"_fmt(log));
      }
    };

    link_and_validate();

    map<sym_t, var_t> vars = {};

    int attributes = gl_get_program<GL_ACTIVE_ATTRIBUTES>(p);
    for (int i = 0; i < attributes; i++) {
      var_t v = var_t::get_attrib(p, i);
      vars.insert({v.name, v});
    }

    int uniforms = gl_get_program<GL_ACTIVE_UNIFORMS>(p);
    for (int i = 0; i < uniforms; i++) {
      var_t v = var_t::get_uniform(p, i);
      vars.insert({v.name, v});
    }

    using entry = pair<int, sym_t>;
    auto compare = [](entry& a, entry& b) { return a.first < b.first; };
    auto entries = vector<entry>();

    for (auto& item : vars) {
      var_t& var  = item.second;
      sym_t  name = item.first;
      if (!var.attrib) continue;
      auto re = regex(R"_(in\s+vec4\s+)_"s + name + ";");
      smatch m;
      regex_search(vs, m, re);
      m.size() == 1 || fail("gl.new_prg: could not determine source position: "s + name);
      entries.emplace_back(m.position(0), name);
    }

    sort(entries.begin(), entries.end(), compare);
    for (int i = 0; i < entries.size(); i++) {
      glBindAttribLocation(p, i, entries[i].second.c_str());
      vars[entries[i].second].location = i;
    }

    link_and_validate();

    entries.clear();

    for (auto& item : vars) {
      var_t& var  = item.second;
      sym_t  name = item.first;
      if (var.attrib) continue;

      if (var.type != GL_SAMPLER_1D        && var.type != GL_SAMPLER_2D         &&
          var.type != GL_SAMPLER_3D        && var.type != GL_SAMPLER_CUBE       &&
          var.type != GL_SAMPLER_1D_SHADOW && var.type != GL_SAMPLER_2D_SHADOW) continue;

      auto re = regex(R"_(uniform\s+sampler[a-zA-Z0-9]+\s+)_"s + name + ";");
      smatch m;
      regex_search(src, m, re);
      m.size() == 1 || fail("gl.new_prg: could not determine source position: "s + name);
      entries.emplace_back(m.position(0), name);
    }

    sort(entries.begin(), entries.end(), compare);
    glUseProgram(p);
    for (int i = 0; i < entries.size(); i++) {
      auto& v = vars[entries[i].second];
      glUniform1i(v.location, i);
    }
    glUseProgram(0);

    check();

    __.prgs[s] = p;
    __.vars[s] = vars;

    if (__.postprocessor) __.postprocessor(s);
  } catch (prg_exception& e) {
  }

  return *this;
}

bool gl_t::operator==(const gl_t& rhs) const {
  return this == &rhs;
}

string gl_t::load(sym_t name) {
  string s{name.str()};
  if (rmr.startswith(s, "st_")) {
    s = s.erase(0, 3);
    string st_src = rmr.slurp(rmr.cfg("base") + "rsc/shadertoy/" + s + ".glsl");
    string st_tmp = rmr.slurp(rmr.cfg("base") + "shadertoy.glsl");
    return rmr.replace(st_tmp, "SHADERTOY_BODY_GOES_HERE_LOL_BBQ", st_src);
  } else {
    return rmr.slurp(rmr.cfg("base") + "%.glsl"_fmt(name));
  }
}

#import "gl_enum_names.h"

const string& gl_t::enum_name(uint e) {
  static auto& table = gl_enum_names();
  table.count(e) || rmr.fatal() << "gl.enum_name: unknown enum:" << e;
  return table[e];
}

#define _(a, b) static_assert(std::is_same<a, b>::value, "type " #a " is not " #b)
_(GLboolean , u8 );
_(GLbyte    , i8 );
_(GLshort   , i16);
_(GLint     , i32);
_(GLint64   , i64);
_(GLubyte   , u8 );
_(GLushort  , u16);
_(GLuint    , u32);
_(GLuint64  , u64);
_(GLsizei   , i32);
_(GLenum    , u32);
_(GLfloat   , float);
_(GLdouble  , double);
#undef _
