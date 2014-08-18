#import "window.h"
#import "view.h"
#import "space.h"
#import "rmr.h"
#import "gl.h"
#import "syphon.h"
#import "fmt.h"
#import "vec.h"
#import "color.h"
#import "wave.h"
#import "counter.h"

#import <GLFW/glfw3.h>
#import <GLFW/glfw3native.h>

#import "nav.h"

using _ = window_t&;

static int& window_count() {
  static int _ = 0;
  return _;
}

struct glfw_initializer_t : counter_t<glfw_initializer_t> {
  glfw_initializer_t() {
    if (solo()) {
      rmr.info("window: initializing glfw");
      glfwInit() || rmr.die("display: failed to initialize glfw");

      glfwSetErrorCallback([](int error, const char* description) {
        rmr.die("win_t: glfw error %: %"_fmt(error, description));
      });

      glfwSetMonitorCallback([](GLFWmonitor* monitor, int event){
        rmr.info("win_t: monitor %"_fmt % (event == GLFW_CONNECTED ? "connected" : "disconnected"));
      });
    }
  }

  ~glfw_initializer_t() {
    if (solo()) {
      rmr.info("window: terminating glfw");
      glfwTerminate();
    }
  }
};

struct window_t::data_t : glfw_initializer_t {
  GLFWwindow*              w                = nullptr;
  unique_ptr<syphon_t>     syphon           = {};
  unique_ptr<gl_t>         gl               = {};
  bool                     hidden           = false;
  bool                     has_clients      = false;
  CGLContextObj            core_context     = nullptr;
  int                      beat             = 0;
  double                   now              = 0;
  double                   start            = 0;
  double                   elapsed          = 0;
  nav_t                    nav              = {};
  uvec2                    allocated        = {};
  img_t                    waveform         = {wave_t::sample_count,    1};
  img_t                    frequency        = {wave_t::frequency_count, 1};
  img_t                    phaseless        = {wave_t::sample_count,    1};
};

void dispatch(GLFWwindow* window, const event_t& e) {
  auto& w = *((window_t*)glfwGetWindowUserPointer(window));
  e(w.nav());
  w.emit(e);
}

window_t::window_t(const hints_t& hints) : __(*new data_t) {
  space_t& space = parent().as<space_t>();

  __.start = rmr.now();

  auto monitor = glfwGetPrimaryMonitor();
  auto mode = glfwGetVideoMode(monitor);

  glfwDefaultWindowHints();

  glfwWindowHint(              GLFW_VISIBLE ,            !hints.hidden);
  glfwWindowHint(            GLFW_RESIZABLE ,          hints.resizable);
  glfwWindowHint(            GLFW_DECORATED ,          hints.decorated);
  glfwWindowHint(       GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR ,                        4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR ,                        1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT ,                     true);

  __.w = glfwCreateWindow(
    hints.width  > 0 ? hints.width  : mode->width,
    hints.height > 0 ? hints.height : mode->height,
    hints.title.c_str(),
    hints.fullscreen ? monitor : nullptr,
    nullptr
  );

  current(true);

  glfwSetWindowUserPointer(__.w, this);

  dispatch(__.w, resize_e(width(), height()));

  name(hints.title);
  position(hints.left, hints.top);

  glfwSetWindowCloseCallback(__.w, [](GLFWwindow* w) {
      dispatch(w, quit_e());
  });

  glfwSetKeyCallback(__.w, [](GLFWwindow* w, int key, int code, int action, int mods) {
    key_e* e = nullptr;
  
    if     (action == GLFW_PRESS  ) e = new keydown_e();
    else if(action == GLFW_RELEASE) e = new keyup_e();
    else if(action == GLFW_REPEAT ) e = new keyrepeat_e();
    else rmr.die("window: unknown key action: %"_fmt(action));

    e->key            = key;
    e->scancode       = code;
    e->shift          = mods & GLFW_MOD_SHIFT;
    e->control        = mods & GLFW_MOD_CONTROL;
    e->alt            = mods & GLFW_MOD_ALT;
    e->super          = mods & GLFW_MOD_SUPER;

    dispatch(w, *e);
    delete e;
  });

  glfwSetCharCallback(__.w, [](GLFWwindow* w, unsigned int codepoint) {
    character_e e(codepoint);
    dispatch(w, e);
  });

  glfwSetWindowFocusCallback(__.w, [](GLFWwindow* w, int focused) {
  });

  glfwSetMouseButtonCallback(__.w, [](GLFWwindow* w, int b, int a, int mods) {
    if (a == GLFW_PRESS) {
      auto e = mousedown_e();

      e.button  = b;
      e.shift   = mods & GLFW_MOD_SHIFT;
      e.control = mods & GLFW_MOD_CONTROL;
      e.alt     = mods & GLFW_MOD_ALT;
      e.super   = mods & GLFW_MOD_SUPER;

      dispatch(w, e);
    } else {
      auto e = mouseup_e();

      e.button  = b;
      e.shift   = mods & GLFW_MOD_SHIFT;
      e.control = mods & GLFW_MOD_CONTROL;
      e.alt     = mods & GLFW_MOD_ALT;
      e.super   = mods & GLFW_MOD_SUPER;

      dispatch(w, e);
    }
  });

  glfwSetCursorEnterCallback(__.w, [](GLFWwindow* w, int entered) {
    if (entered) dispatch(w, mouseenter_e{});
    else         dispatch(w, mouseleave_e{});
  });

  glfwSetCursorPosCallback(__.w, [](GLFWwindow* w, double x, double y) {
    int width, height;
    glfwGetWindowSize(w, &width, &height);
    dispatch(w, mousemove_e{x, height - y});
  });

  glfwSetWindowSizeCallback(__.w, [](GLFWwindow* w, int width, int height) {
    dispatch(w, resize_e(width, height));
    rmr.info("window: resize: %x%"_fmt(width, height));
  });

  glfwSetScrollCallback(__.w, [](GLFWwindow* w, double x, double y) {
    dispatch(w, scroll_e{x, y});
  });

  glfwSetWindowRefreshCallback  (__.w, [](GLFWwindow* w                       ) { rmr.info("window refresh"); });
  glfwSetWindowIconifyCallback  (__.w, [](GLFWwindow* w, int iconified        ) { rmr.info("iconify");        });
  glfwSetFramebufferSizeCallback(__.w, [](GLFWwindow* w, int width, int height) { rmr.info("buffer size");    });
  glfwSetWindowPosCallback      (__.w, [](GLFWwindow* w, int x, int y         ) { rmr.info("window pos");     });

  NSOpenGLContext* ns_ctx = glfwGetNSGLContext(__.w);
  CGLContextObj ctx_a = (CGLContextObj)[ns_ctx CGLContextObj];
  CGLContextObj ctx_b = CGLGetCurrentContext();

  ctx_a == ctx_b || rmr.die("win: retrieving cgl context failed");

  __.core_context = ctx_b;

  __.syphon = std::make_unique<syphon_t>(*this);
  __.gl     = std::make_unique<    gl_t>(*this);

  uint fbo;
  uint rbo;
  uint tex;

  gl()
  .new_fbo("frame", fbo)
  .new_rbo("frame", rbo)
  .new_tex("frame", tex)
  .new_tex("waveform")
  .new_tex("frequency")
  .new_tex("phaseless")
  .new_vbo("quad")
  .upload_ccw_quad("quad")
  .supplier("win_waveform",        [&](gl_t& gl, sym_t var) { gl.value(var, "waveform"                            ); })
  .supplier("win_frequency",       [&](gl_t& gl, sym_t var) { gl.value(var, "frequency"                           ); })
  .supplier("win_phaseless",       [&](gl_t& gl, sym_t var) { gl.value(var, "phaseless"                           ); })
  .supplier("win_elapsed",         [&](gl_t& gl, sym_t var) { gl.value(var, __.elapsed                            ); })
  .supplier("win_now",             [&](gl_t& gl, sym_t var) { gl.value(var, __.now                                ); })
  .supplier("win_beat",            [&](gl_t& gl, sym_t var) { gl.value(var, __.beat                               ); })
  .supplier("win_intensity",       [&](gl_t& gl, sym_t var) { gl.value(var, rmr.wave().m().intensity              ); })
  .supplier("win_resolution",      [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.size()                         ); })
  .supplier("win_aspect_ratio",    [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.aspect_ratio()                 ); })
  .supplier("win_drag",            [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.drag()                         ); })
  .supplier("win_drag_start",      [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.drag_start()                   ); })
  .supplier("win_cursor",          [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.cursor()                       ); })
  .supplier("win_zoom",            [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.zoom()                         ); })
  .supplier("win_trackball",       [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.trackball()                    ); })
  .supplier("win_trackball_start", [&](gl_t& gl, sym_t var) { gl.value(var, trackball_project(__.nav.drag_start())); })
  .supplier("win_trackball_end",   [&](gl_t& gl, sym_t var) { gl.value(var, trackball_project(__.nav.cursor())    ); })
  .supplier("win_fps",             [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.fps()                          ); })
  .supplier("win_rts",             [&](gl_t& gl, sym_t var) { gl.value(var, mat4::identity()                      ); })
  // shader toy variables
  .supplier("iGlobalTime",         [&](gl_t& gl, sym_t var) { gl.value(var, __.elapsed                            ); })
  .supplier("iResolution",         [&](gl_t& gl, sym_t var) { gl.value(var, __.nav.width(), __.nav.height(), 0.0  ); })
  .supplier("iMouse",              [&](gl_t& gl, sym_t var) { 
    if (__.nav.cursor_down()) {
      gl.value(var, 
        (__.nav.cursor    ().x() * 0.5 + 0.5) * __.nav.width (),
        (__.nav.cursor    ().y() * 0.5 + 0.5) * __.nav.height(),
        (__.nav.drag_start().x() * 0.5 + 0.5) * __.nav.width (),
        (__.nav.drag_start().y() * 0.5 + 0.5) * __.nav.height()
      );
    } else {
      gl.value(var, 
        (__.nav.drag_end  ().x() * 0.5 + 0.5) *  __.nav.width (),
        (__.nav.drag_end  ().y() * 0.5 + 0.5) *  __.nav.height(),
        (__.nav.drag_start().x() * 0.5 + 0.5) * -__.nav.width (),
        (__.nav.drag_start().y() * 0.5 + 0.5) * -__.nav.height()
      );
    }
  })
  .supplier("iDate", [&](gl_t& gl, sym_t var) { 
    time_t t      = time(NULL);
    tm* p         = localtime(&t);
    float year    = p->tm_year + 1900;
    float month   = p->tm_mon;
    float day     = p->tm_mday;
    float seconds = p->tm_hour * 60.0 * 60.0 + p->tm_min * 60.0 + p->tm_sec;
    gl.value(var, year, month, day, seconds);
  })
  ;

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

  GLenum buffer = GL_COLOR_ATTACHMENT0;
  glDrawBuffers(1, &buffer);
};

window_t::~window_t() {
  __.syphon.reset(nullptr);
  __.gl.reset(nullptr);
  current(false);
  glfwDestroyWindow(__.w);
  delete &__;
}

nav_t& window_t::nav() {
  return __.nav;
}

_ window_t::beat() {
  __.beat++;
  return *this;
}

bool window_t::current() const {
  return glfwGetCurrentContext() == __.w;
}

_ window_t::current(bool x) {
  if (x) {
    glfwGetCurrentContext() == nullptr || rmr.die("window.current: another context already current");
    glfwMakeContextCurrent(__.w);
  } else {
    glfwGetCurrentContext() == __.w || rmr.die("window.current: context was not current");
    glfwMakeContextCurrent(nullptr);
  }

  return *this;
}

CGLContextObj& window_t::core_context() {
  return __.core_context;
}

img_t window_t::screenshot() {
  glReadBuffer(GL_FRONT);

  int w, h;
  glfwGetWindowSize(__.w, &w, &h);

  img_t dest;
  dest.resize(w, h);
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, dest.bytes());
  return dest;
}

_ window_t::closing(bool v) {
  glfwSetWindowShouldClose(__.w, v);
  return *this;
}

bool window_t::closing() {
  return glfwWindowShouldClose(__.w);
}

int window_t::width()  const { int w, h; glfwGetWindowSize(__.w, &w, &h); return w; }
int window_t::height() const { int w, h; glfwGetWindowSize(__.w, &w, &h); return h; }

uvec2 window_t::size() const {
  int w, h;
  glfwGetWindowSize(__.w, &w, &h);
  return uvec2(w, h);
}

int window_t::left() {
  int l;
  glfwGetWindowPos(__.w, &l, &rmr.ti());
  return l;
}

int window_t::top() {
  int t;
  glfwGetWindowPos(__.w, &rmr.ti(), &t);
  return t;
}

_ window_t::left(int l) {
  glfwSetWindowPos(__.w, l, top());
  return *this;
}

_ window_t::top(int t) {
  glfwSetWindowPos(__.w, left(), t);
  return *this;
}

_ window_t::size(int w, int h) {
  glfwSetWindowSize(__.w, w, h);
  return *this;
}

_ window_t::position(int l, int t) {
  glfwSetWindowPos(__.w, l, t);
  return *this;
}

gl_t& window_t::gl() {
  return *__.gl;
}

syphon_t& window_t::syphon() {
  return *__.syphon;
}

void window_t::operator()(const tick_e& e) {
  glfwPollEvents();
  e(__.nav);
}

void window_t::operator()(const rename_e& e) {
  glfwSetWindowTitle(__.w, name().c_str());
}

void window_t::operator()(const show_e& e) {
  glfwShowWindow(__.w);
}

void window_t::operator()(const hide_e& e) {
  glfwHideWindow(__.w);
}

void window_t::operator()(const render_e& e) {
  uint fbo = gl().get_fbo("frame");
  uint rbo = gl().get_rbo("frame");
  uint tex = gl().get_tex("frame");

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);

  if (rmr.changed(__.allocated, size())) {
    gl().image("frame", __.allocated.x(), __.allocated.y());
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, __.allocated.x(), __.allocated.y());
  }

  __.now = e.tick.time;

  if (__.start == 0.0) __.start = __.now;
  __.elapsed = __.now - __.start;

  while (rmr.wave().empty()) { }

  {
    int i = 0;
    for (auto x : rmr.wave().m().waveform) {
      u8 _ = (x * 0.5 + 0.5) * 255.0;
      __.waveform(i, 0) = {_, _, _, 255};
      i++;
    }
    gl().image("waveform", __.waveform);
  }
  { 
    int i = 0;
    for (auto x : rmr.wave().m().frequency) {
      u8 _ = x * 255.0;
      __.frequency(i, 0) = {_, _, _, 255};
      i++;
    }
    gl().image("frequency", __.frequency);
  }
  {
    int i = 0;
    for (auto x : rmr.wave().m().phaseless) {
      u8 _ = (x * 0.5 + 0.5) * 255.0;
      __.phaseless(i, 0) = {_, _, _, 255};
      i++;
    }
    gl().image("phaseless", __.phaseless);
  }

  draw_e draw{e.tick};
  draw.w = width();
  draw.h = height();
  draw.x = 0;
  draw.y = 0;

  broadcast(draw);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  gl()
  .prepare("copy")
  .value("source", "frame")
  .pack({"position"}, "quad")
  .ready()
  .triangles()
  .draw_arrays()
  .done()
  ;

  bool had_clients = __.has_clients;
  __.has_clients = syphon().has_clients();
  if (rmr. rising_edge(had_clients, __.has_clients)) rmr << "win.render: +syphon";
  if (rmr.falling_edge(had_clients, __.has_clients)) rmr << "win.render: -syphon";

  if (__.has_clients) {
    syphon().bind();
    gl()
    .prepare("copy")
    .value("source", "frame")
    .pack({"position"}, "quad")
    .ready()
    .triangles()
    .draw_arrays()
    .done()
    ;
    syphon().publish();
  }

  glfwSwapBuffers(__.w); 

  if (e.tick.count < 10) gl().check();
}

void window_t::operator()(const verify_e& e) {
  for_descendants([](top_t& descendant) {
    descendant.is<view_t>() || rmr.die("window.verify: children must be views");
  });
}

void window_t::operator()(const draw_e& e) {
  gl()
  .aperture(e.x, e.y, e.w, e.h)
  .clear_color("black"_color)
  .clear();
}
