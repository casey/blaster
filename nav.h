#import "quat.h"

constexpr float trackball_size = 2.0 / 3.0;

static vec3 trackball_project(const vec2 v) {
  float radius = trackball_size;
  float m = v.magnitude();
  float z;
  if (m < radius * rmr.sqrt(1.0 / 2.0)) { // on sphere
    z = rmr.sqrt(radius * radius - m * m);
  } else { // on hyperbola
    float t = radius / rmr.sqrt(2);
    z = t * t / m;
  }
  return v.extend(z);
}

quat trackball(vec2 start, vec2 end) {
  if (start == end) return quat::identity();

  // project start and end to trackball surface
  vec3 s = trackball_project(start);
  vec3 e = trackball_project(end  );

  // axis of rotation
  vec3 a = e.cross(s);

  // angle of rotation
  vec3 d = s - e;
  float t = d.magnitude() / (2.0 * trackball_size);

  t = rmr.clamp(t, -1.0, 1.0);

  float phi = 2.0 * rmr.asin(t);

  return quat::from_aa(a, phi);
}

struct nav_t : null_target_t {
  vec2           _size              = {1.0, 1.0};
  bool           _cursor_down       = false;
  bool           _cursor_out        = false;
  vec2           _cursor            = {0.0, 0.0};
  vec2           _drag              = {0.0, 0.0};
  vec2           _drag_start        = {0.0, 0.0};
  vec2           _drag_end          = {0.0, 0.0};
  vec2           _last_cursor       = {0.0, 0.0};
  mat4           _trackball         = mat4::identity();
  mat4           _trackball_current = mat4::identity();
  mat4           _fps               = mat4::identity();
  float          _zoom              = 0.0;
  map<int, bool> _keys              = {};

  vec2  cursor()       { return _cursor;                         }
  vec2  size()         { return _size;                           }
  float zoom()         { return _zoom;                           }
  vec2  drag()         { return _drag;                           }
  vec2  drag_start()   { return _drag_start;                     }
  vec2  drag_end()     { return _drag_end;                       }
  mat4  trackball()    { return _trackball * _trackball_current; }
  mat4  fps()          { return _fps;                            }
  float width()        { return size().x();                      }
  float height()       { return size().y();                      }
  float aspect_ratio() { return width() / height();              }
  bool  cursor_down()  { return _cursor_down;                    }

  nav_t() { }

  void operator()(const mouseup_e& e) override {
    _cursor_down = false;
    _trackball = trackball();
    _trackball_current = mat4::identity();
    _drag_end = _cursor;
  }

  void operator()(const mousemove_e& e) override {
    _cursor = (vec2(e.x, e.y) / _size) * 2.0 - 1.0;
    if (_cursor_down) {
      _drag += (_cursor - _last_cursor) * -0.5;
      _trackball_current = ::trackball(_drag_start, _cursor).to_matrix();
    }
    _last_cursor = _cursor;
  }

  void operator()(const mousedown_e&) override {
    _cursor_down = true;
    _drag_start = _cursor;
  }

  void operator()(const keydown_e& e) override {
    _keys[e.key] = true;
  }

  void operator()(const keyup_e& e) override {
    _keys[e.key] = false;
  }

  void operator()(const mouseleave_e&) override {
    _cursor_out  = true;
  }

  void operator()(const mouseenter_e&) override {
    _cursor_out  = false;
  }

  void operator()(const scroll_e& e) override {
    _zoom += e.y;
  }

  void operator()(const resize_e& e) override {
    _size = vec2(e.width, e.height);
  }

  void operator()(const tick_e& e) override {
    float speed_factor   = e.dt;
    float movement_speed = speed_factor;
    float rotation_speed = speed_factor * 0.5;

    if (_keys[GLFW_KEY_D    ]) _fps.translate_x( movement_speed);
    if (_keys[GLFW_KEY_A    ]) _fps.translate_x(-movement_speed);

    if (_keys[GLFW_KEY_E    ]) _fps.translate_y( movement_speed);
    if (_keys[GLFW_KEY_C    ]) _fps.translate_y(-movement_speed);

    if (_keys[GLFW_KEY_S    ]) _fps.translate_z( movement_speed);
    if (_keys[GLFW_KEY_W    ]) _fps.translate_z(-movement_speed);

    if (_keys[GLFW_KEY_UP   ]) _fps.rotate_x   ( rotation_speed);
    if (_keys[GLFW_KEY_DOWN ]) _fps.rotate_x   (-rotation_speed);
    if (_keys[GLFW_KEY_LEFT ]) _fps.rotate_y   ( rotation_speed);
    if (_keys[GLFW_KEY_RIGHT]) _fps.rotate_y   (-rotation_speed);
  }
};
