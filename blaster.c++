#import "view.h"
#import "sym.h"
#import "rmr.h"
#import "fmt.h"
#import "vec.h"
#import "gl.h"
#import "route.h"
#import "timer.h"
#import "window.h"
#import "shortcut.h"
#import "key.h"
#import "color.h"
#import "view.grid.h"
#import "push.h"
#import "ring.h"
#import "wave.h"

#import <OpenGL/gl3.h>

static uint next_buffer = 0;

constexpr uint depth_limit = 16;

struct buffer_t {
  gl_t& gl;
  uint  fbo  = 0;
  uint  rbo  = 0;
  uint  tex  = 0;
  uint  id   = next_buffer++;
  uvec2 size = {0, 0};
  sym_t sym  = "buffer%"_fmt(id);

  buffer_t(gl_t& gl) : gl(gl) {
    gl
    .new_fbo(sym, fbo)
    .new_rbo(sym, rbo)
    .new_tex(sym, tex)
    ;

    // todo: remove direct calls to opengl

    gl.bind_fbo(sym);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

    gl.bind_rbo(sym);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    GLenum buffer = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &buffer);

    resize({1, 1});
  }

  void bind() {
    gl.bind_fbo(sym);
  }

  void resize(uvec2 new_size) {
    if (!rmr.changed(size, new_size)) return;

    gl.image(sym, size.x(), size.y());
    gl.bind_rbo(sym);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x(), size.y());
  }
};

vector<u32string>& game_over_lines() {
  static vector<u32string> _ = {
    U"                ",
    U"                ",
    U"                ",
    U"   GAME  OVER   ",
    U"                ",
    U"                ",
    U"                ",
    U"   THANKS       ",
    U"   FOR          ",
    U"   PLAYING!     ",
    U"                ",
    U"                ",
    U"                ",
  };

  return _;
}

vector<u32string>& overlay_lines() {
  static vector<u32string> _ = {
    U"                ",
    U"  1UP4PLAY v2.0 ",
    U"                ",
    U"  STAGE SELECT  ",
    U"                ",
    U"> NARGA         ",
    U"  BARNEY        ",
    U"  HACHIKO       ",
    U"  MINIKOMI      ",
    U"  RUKI-CHAN     ",
    U"  SIGE          ",
    U"  CHIBI-TECH    ",
    U"                "
  };

  return _;
}

int overlay_rows() {
  return overlay_lines().size() + 2;
}

int overlay_cols() {
  size_t cols = 1;
  for (auto line : overlay_lines()) {
    cols = std::max(cols, line.size() + 2);
  }
  return cols;
}

struct blaster : view_t {
  vector<vector<sym_t>>          history        {{}};
  vector<sym_t>                  saved          {};
  vector<sym_t>                  filters        {};
  buffer_t                       buffers[2]     {gl(), gl()};
  uint                           i              {0};
  bool                           unwinding      {};
  map<shortcut_t, fun_t<void()>> shortcuts      {};
  map<gizmo_t,    fun_t<void()>> cell_commands  {};
  map<gizmo_t,    uint>          cell_colors    {};
  bool                           ex             {false};
  string                         command        {};
  grid_v&                        overlay        {spawn<grid_v>(overlay_cols(), overlay_rows())};
  uint                           selected_artist{0};
  bool                           game_over      {false};
  push_t                         push           {*this};
  timer_t                        frame_timer    {};
  ring_t<double, 60>             frame_times    {};
  uint                           frame          {0};
  double                         gain           {1.0};
  string                         last_command   {};

  blaster() {
    gl()
    .new_vbo("quad")
    .upload_ccw_quad("quad")
    .supplier("source", [&](gl_t& gl, sym_t var) { gl.value(var, source().sym); })
    .postprocessor([&](auto name) { postprocess(name); })
    .new_prg("blaster")
    ;

    current().push_back("test");

    overlay.foreground("white"_c).background("black"_c).hide();

    if (is_filter("wip")) current().push_back("wip");

    on("shift-;", [&]() { ex = true; });

    for (int i = (int)gizmo_t::cell_first; i <= (int)gizmo_t::cell_last; i++) {
      on((gizmo_t)(i), i, [&](){ last_command = "push top"; push_top(); });
    }
  }

  void update_overlay() {
    overlay.clear();

    if (game_over) {
      int y = overlay_rows() - 2;
      for (auto line : game_over_lines()) {
        overlay.set(1, y--, 1, 0.25, line);
      }
    } else {
      int y = overlay_rows() - 2;

      auto& lines = overlay_lines();

      int  artist_start = 0;
      char selection_char = ' ';
      for (int i = 0; i < lines.size(); i++) {
        char c = lines[i][0];
        if (c != ' ') {
          artist_start = i;
          selection_char = c;
          break;
        }
      }

      int artist_count = lines.size() - artist_start - 1;

      // kind of want it to flash or something when selected

      int i = 0;
      for (auto line : overlay_lines()) {
        bool selected = false;
        if (i >= artist_start) {
          if ((i - artist_start) == (selected_artist % artist_count)) {
            selected = true;
            line[0] = selection_char;
          } else {
            line[0] = ' ';
          }
        }
        overlay.set(1, y--, 1, selected ? 0.50 : 0.25, line);
        i++;
      }
    }
  }

  void postprocess(sym_t name) {
    uint program = gl().get_prg(name);

    filters.clear();

    // todo: remove direct calls to opengl
    int filter_count;
    glGetProgramStageiv(program, GL_FRAGMENT_SHADER, GL_ACTIVE_SUBROUTINES, &filter_count);

    int max_length;
    glGetProgramStageiv(program, GL_FRAGMENT_SHADER, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &max_length);

    char* s = new char[max_length];
    for (int i = 0; i < filter_count; i++) {
      int written;
      glGetActiveSubroutineName(program, GL_FRAGMENT_SHADER, i, max_length, &written, s);
      filters.push_back(s);
    }
    delete[] s;

    for (auto& pipeline : history) {
      for (auto i = pipeline.size(); i-- > 0;) {
        if (!is_filter(pipeline[i])) pipeline.erase(pipeline.begin() + i);
      }
    }
  }

  uint index(sym_t filter) {
    for (int i = 0; i < filters.size(); i++) {
      if (filters[i] == filter) return i;
    }

    rmr.die("blaster: index: unknown filter: %"_fmt(filter));
  }

  bool is_filter(sym_t filter) {
    for (int i = 0; i < filters.size(); i++) {
      if (filters[i] == filter) return true;
    }
    return false;
  }

  void      swap       () { i++;                         }
  buffer_t& source     () { return buffers[(i    ) % 2]; }
  buffer_t& destination() { return buffers[(i + 1) % 2]; }

  void on(gizmo_t g, uint color, fun_t<void()> handler) {
    push.color(g, color);
    if (cell_commands.count(g) > 0) rmr.die("on: gizmo already mapped");
    cell_commands[g] = handler;
    cell_colors  [g] = color;
  }

  void on(const string& str, fun_t<void()> handler) {
    auto s = shortcut_t(str);
    shortcuts[s] = handler;
  }

  void execute(const string& c) {
    rmr << ":"s + c;

    if (c == "gameover") {
      game_over = !game_over;
    } else {
      for (auto f : filters) {
        if (f.str() == c) {
          checkpoint();
          current().push_back(f);
          while(current().size() > depth_limit) current().erase(current().begin());
          return;
        }
      }
    }
  }

  void operator()(const tick_e& e) override {
    if (!e.first()) {
      frame_times.write(frame_timer.elapsed());
    }
    frame_timer.reset();

    push(e);
    push.display(' ');

    auto set = [&](int x, int y, const string& s){
      int count = std::min(s.length(), size_t(8));
      for (int i = 0; i < count; i++) {
        int real_x = x * 8 + i;
        for (int _ = 1; _ <= x; _ += 2) {
          real_x++;
        }
        push.display(real_x, y, s[i]);
      }
    };

    int i = 0;
    for (auto f : current()) {
      set(i % 8, i / 8, f.str());
      i++;
    }

    set(0, 3, "#%"_fmt(frame));
    set(1, 3, "%ms"_fmt(rmr.ms(rmr.mean(frame_times))));
    set(2, 3, "epoch %"_fmt(epoch()));
    set(3, 3, "gain %"_fmt(gain));
    set(4, 3, last_command);
    set(5, 3, command);
    if (command.size() > 8) set(6, 3, command.substr(8));
    frame++;
  }

  void operator()(const push_e& e) override {
    auto g = $(e.gizmo);
    rmr.info("blaster: push event: % % %"_fmt(e.type, g, e.value));

    if (g.cell()) {
      if (e.down()) { push.color(e.gizmo,   3); }
      if (e.up  ()) { push.color(e.gizmo, cell_colors.count(e.gizmo) > 0 ? cell_colors[e.gizmo] : 104); }
    }

    if (e.gizmo == gizmo_t::button25 && e.down()) {
      rewind();
    } else if (e.gizmo == gizmo_t::button24 && e.down()) {
      checkpoint();
      pop_top();
    } else if (e.gizmo == gizmo_t::slider && e.set()) {
      gain = e.value * 5;
    } else if (e.gizmo == gizmo_t::button26 && e.down()) {
      overlay.toggle();
    } else if (e.gizmo == gizmo_t::knob9 && e.set() && !overlay.hidden()) {
      if (e.value > 0) {
        selected_artist++;
      } else {
        selected_artist--;
      }
    } else if ($(e.gizmo).cell() && e.down()) {
      if (cell_commands.count(e.gizmo) > 0) {
        checkpoint();
        cell_commands[e.gizmo]();
      }
    }
  }

  void operator()(const keydown_e& e) override {
    if (ex && e.key == GLFW_KEY_BACKSPACE) {
      if (command.size() > 1) command.erase(command.size() - 1, 1);
    } else if (ex && e.key == GLFW_KEY_ENTER) {
      ex = false;
      command.erase(0, 1);
      execute(command);
      command = "";
    } else {
      shortcut_t s{e};
      if (shortcuts.count(s) > 0) shortcuts[s]();
    }
  }

  void operator()(const character_e& e) override {
    if (ex) {
      command += e.str == " "s ? "_"s : e.str;
    } else {
      checkpoint();
      char c = e.str[0];
      switch(c) {
#define _(CHAR, CMD) case CHAR: last_command = #CMD; rmr << last_command; CMD; break;
        _(' ', push_top()   );
        _('0', reset_beat() );
        _('a', advance()    );
        _('c', cycle()      );
        _('d', roll_down()  );
        _('j', push_top()   );
        _('k', push_bottom());
        _('m', multiply()   );
        _('p', nuke()       );
        _('r', recall()     );
        _('s', save()       );
        _('t', roll_up()    );
        _('u', undo()       );
        _('w', waffle()     );
        _('x', randomize()  );
        _('z', unwind()     );
        _('?', print() );
#undef _
        default: rewind();
      }
    }
  }

  void operator()(const draw_e& e) override {
    update_overlay();

    if (unwinding && (unwinding = epoch() > 0)) {
      undo();
    }

    // todo: remove direct opengl call
    int original_fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);

    source().resize(uvec2(e.w, e.h));
    source().bind();
    render("off");

    if (current().size() > depth_limit) {
      rmr << "blaster: pipeline depth over limit:" << current().size();
      while(current().size() > depth_limit) {
        int i = rmr.random_index(current().size());
        current().erase(current().begin() + i);
      }
    }

    for (auto filter : current()) {
      destination().resize(uvec2(e.w, e.h));
      destination().bind();
      render(filter);
      swap();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);

    render("identity");
  }

  void render(sym_t filter) {
    gl().prepare("blaster");

    uint i = index(filter);

    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &i);

    double pump = rmr.wave().m().intensity * gain;
    if (pump < 0.0) pump = 0.0;

    gl()
    .pack({"position"}, "quad")
    .value("pump", pump)
    .ready()
    .triangles()
    .draw_arrays()
    .done()
    ;
  }

  vector<sym_t>& current() {
    return history.back();
  }

  uint epoch() {
    return history.size() - 1;
  }

  void checkpoint() {
    history.push_back(current());
  }

  void rewind() {
    if (history.size() > 1) history.pop_back();
  }

  void undo() {
    rewind();
    rewind();
  }

  void waffle() {
    rewind();
    auto top = current();
    rewind();
    auto next = current();
    rewind();
    history.push_back(top);
    history.push_back(next);
  }

  void unwind() {
    unwinding = true;
    undo();
  }

  sym_t next() {
    sym_t f = "identity";
    while (f == "identity" || f == "off" || f == "heart") {
      f = random();
    }
    return f;
  }

  sym_t random() {
    return rmr.choice(filters);
  }

  sym_t push_top() {
    auto  f = next();
    auto& c = current();
    c.push_back(f);
    while (c.size() > depth_limit) c.erase(c.begin());
    return f;
  }

  sym_t push_bottom() {
    auto f = next();
    auto& c = current();
    c.insert(c.begin(), f);
    while (c.size() > depth_limit) c.erase(c.end() - 1);
    return f;
  }

  void pop_top() {
    if (current().size() > 0) current().pop_back();
  }

  void pop_bottom() {
    if (current().size() > 0) current().erase(current().begin());
  }

  void clear() {
    current().clear();
  }

  void roll_down() {
    auto old   = current();
    auto count = current().size();
    for (int i = 0; i < count; i++) {
      int j = (i + 1) % count;
      current()[i] = old[j];
    }
  }

  void save() {
    saved = current();
    rewind();
  }

  void recall() {
    if (!saved.empty()) {
      current() = saved;
    }
  }

  uint beat = 0;

  void reset_beat() {
    beat = 0;
    rewind();
  }

  void cycle() {
    if (beat % 4 < 3) {
      push_top();
    } else {
      auto i = history.end();
      i -= 5;
      if (i < history.begin()) i = history.begin();
      current() = *i;
    }
    beat++;
  }

  void multiply() {
    if (beat % 4 < 3) {
      current().push_back("zoom_out");
    } else {
      auto i = history.end();
      i -= 5;
      if (i < history.begin()) i = history.begin();
      current() = *i;
    }
    beat++;
  }

  void advance() {
    if (beat % 4 < 3) {
      push_top();
    } else {
      auto i = history.end();
      i -= 4;
      if (i < history.begin()) i = history.begin();
      current() = *i;
    }
    beat++;
  }

  void nuke() {
    auto& c = current();
    c.clear();

    for (int i = 0; i < depth_limit; i++) {
      push_top();
    }
  }

  void print() {
    auto& c = current();

    for (int i = 0; i < c.size(); i++) {
      if (i > 0) std::cerr << ' ';
      std::cerr << c[i];
    }

    std::cerr << std::endl;
  }

  void randomize() {
    auto old = current();
    clear();
    while (old.size() > 0) {
      auto i = rmr.random_index(old.size());
      auto f = old[i];
      old.erase(old.begin() + i);
      current().push_back(f);
    }
  }

  void roll_up() {
    auto old   = current();
    auto count = current().size();
    for (int i = 0; i < count; i++) {
      int j = (i - 1) % count;
      current()[i] = old[j];
    }
  }
};

struct blaster_route : route_t {
  string path() override { return "blaster"; }
  vector<string> params() override { return {}; }
  view_t& operator()(window_t& window, const map<string, string>& args) override {
    return window.spawn<blaster>();
  }
} blaster_route_instance;
