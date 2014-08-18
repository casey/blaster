#version 410 core
#extension GL_ARB_shading_language_include: require
#include <common.glsl>

uniform sampler2D win_waveform;

//!vertex

layout(location = 0) in vec4 position;
out vec2 uv;
out vec2 pos;

void main(void) {
  pos         = position.xy;
  uv          = position.xy * 0.5 + 0.5;
  gl_Position = position;
}

//!fragment

in vec2 pos;
in vec2 uv;
layout(location = 0) out vec4 color;

void render_drag() {
  vec2 muv = fract(uv + win_drag);
  float d = min(abs((1.0 - muv.x) - muv.y), abs(muv.x - muv.y));
  if (d < (0.1 + win_intensity * 0.2)) {
    color.r = 1 - distance(pos, win_cursor);
    color.g = 1 - distance(pos, win_drag_start);
    color.b = 0.0;
    color.a = 1.0;
    color.b = floor(muv.x * 10) / 10.0;
  } else {
    color = texture(win_waveform, vec2(muv.x, 0));
  }
}

float fps_scene(vec3 p) {
  vec3 q = op_repeat(p, vec3(3, 2.5, 3.5));
  return d_cube(q, 1.0);
}

void render_fps() {
  march_cam_t cam       = march_cam(win_fps, vec3(0, 0, 0), win_aspect_ratio, uv);
  const float delta     = 0.001;
  const float max_depth = 12.0;
  float       dist      = 0.02;
  float       t         = 0.5;
  vec3        pos       = vec3(0, 0, 0);
  
  for (int i = 0; i < 180; i++) {
    if ((t > max_depth) || (abs(dist) < delta)) break;
    pos = cam.origin + cam.ray * t;
    dist = fps_scene(pos);
    t += dist;
  }

  if (t > max_depth) discard;
  
  vec3 normal = vec3(
    dist - fps_scene(pos - vec3(delta, 0,     0)),
    dist - fps_scene(pos - vec3(0,     delta, 0)),
    dist - fps_scene(pos - vec3(0,     0,     delta))
  );
  normal = normalize(normal);
  color = vec4(normal, 1.0);
}

float trackball_scene(vec3 p, vec3 b) {
  return op_u(
    d_sphere(p, (2.0 / 3.0)), 
    d_sphere(b - win_trackball_end,   0.1),
    d_sphere(b - win_trackball_start, 0.1)
  );
}

void render_trackball() {
  vec2        ruv            = uv - 0.5;
  float       orbit_distance = 3;
  vec3        s_cam_pos      = vec3(0, 0, orbit_distance);
  vec3        s_world_pix    = vec3(ruv.x * win_aspect_ratio, ruv.y, orbit_distance - 1);
  vec3        s_rel_vec      = normalize(s_world_pix - s_cam_pos);
  march_cam_t cam            = march_cam(win_trackball, s_cam_pos, win_aspect_ratio, uv);

  const float delta     = 0.001;
  const float max_depth = 12.0;
  float       dist      = 0.02;
  float       t         = 0.5;
  vec3        pos       = vec3(0, 0, 0);
  vec3        s_pos     = vec3(0, 0, 0);
  
  for (int i = 0; i < 180; i++) {
    pos = cam.origin + cam.ray * t;
    s_pos = s_cam_pos + s_rel_vec * t;
    dist = trackball_scene(pos, s_pos);
    t += dist;
    if (t > max_depth) discard;
    if (abs(dist) < delta) break;
  }

  vec3 dx   = pos - vec3(delta,     0,     0);
  vec3 dy   = pos - vec3(0,     delta,     0);
  vec3 dz   = pos - vec3(0,         0, delta);
  vec3 s_dx = s_pos - vec3(delta,     0,     0);
  vec3 s_dy = s_pos - vec3(0,     delta,     0);
  vec3 s_dz = s_pos - vec3(0,         0, delta);
  
  vec3 normal = vec3(
    dist - trackball_scene(dx, s_dx),
    dist - trackball_scene(dy, s_dy),
    dist - trackball_scene(dz, s_dz)
  );

  normal = normalize(normal);
  color = vec4(normal, 1.0);
}

void main(void) {
  int mode = win_beat % 3;
  if      (mode == 0) render_drag();
  else if (mode == 1) render_fps();
  else                render_trackball();
}
