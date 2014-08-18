const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 red   = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 blue  = vec4(0.0, 0.0, 1.0, 1.0);
const vec4 gray  = vec4(0.5, 0.5, 0.5, 1.0);
const vec4 grey  = vec4(0.3, 0.3, 0.3, 1.0);

const float pi  = 3.14159265;
const float tau = 6.28318530;

float turns(float x) { return pi * 2 * x; }

vec4 invert(vec4 _) { return vec4(1 - _.rgb, 1); }

vec3 transform_direction(mat4 m, vec3 v                   ) { return (m * vec4(v, 0.0)).xyz;                }
vec3 transform_point    (mat4 m, vec3 v                   ) { return (m * vec4(v, 1.0)).xyz;                }
vec3 transform_direction(mat4 m, float x, float y, float z) { return transform_direction(m, vec3(x, y, z)); }
vec3 transform_point    (mat4 m, float x, float y, float z) { return transform_point(m, vec3(x, y, z));     }

float op_u     (float a, float b         ) { return min(a, b);                    }
float op_u     (float a, float b, float c) { return min(min(a, b), c);            }
float op_sub   (float a, float b         ) { return max(a, -b);                   }
vec3  op_repeat(vec3 p, vec3 c           ) { return mod(p, c) - 0.5 * c;          }
vec3  op_repeat(vec3 p, float c          ) { return op_repeat(p, vec3(c, c, c));  }
float d_sphere (vec3 p, float radius     ) { return length(p) - radius;           }
float d_sphere (vec3 p                   ) { return d_sphere(p, 1.0);             }
float d_box    (vec3 p, vec3 b           ) { return length(max(abs(p) - b, 0.0)); }
float d_cube   (vec3 p, float l          ) { return d_box(p, vec3(l, l, l));      }
float d_cube   (vec3 p                   ) { return d_box(p, vec3(1, 1, 1));      }
float d_half   (vec3 p                   ) { return p.x;                          }

float d_torus(vec3 p, float radius, float diameter) {
  vec2 q = vec2(length(p.xz)-radius,p.y);
  return length(q)-diameter;
}

struct march_cam_t {
  vec3 origin;
  vec3 ray;
};

march_cam_t march_cam(
  mat4 transform,
  vec3 camera_position,
  float aspect_ratio,
  vec2 uv
) {
  vec3 cam_pos      = transform_point    (transform, camera_position);
  vec3 cam_look     = transform_direction(transform, 0, 0, -1);
  vec3 cam_up       = transform_direction(transform, 0, 1,  0);
  vec3 side_norm    = normalize(cross(cam_look, cam_up));
  vec3 up_norm      = normalize(cross(side_norm, cam_look));
  vec3 world_facing = cam_pos + cam_look;
  vec2 ruv          = uv - 0.5;
  vec3 world_pix    = world_facing + ruv.x * side_norm * aspect_ratio + ruv.y * up_norm;
  vec3 rel_vec      = normalize(world_pix - cam_pos);
  march_cam_t result;
  result.origin = cam_pos;
  result.ray    = rel_vec;
  return result;
}

uniform float     win_now;
uniform float     win_elapsed;
uniform int       win_beat;
uniform vec2      win_resolution;
uniform vec2      win_inv_resolution;
uniform float     win_aspect_ratio;
uniform float     win_intensity;

uniform vec2  win_cursor;
uniform mat4  win_trackball;
uniform mat4  win_fps;
uniform mat4  win_rts;
uniform vec2  win_drag;
uniform vec2  win_drag_start;
uniform float win_zoom;

uniform vec3 win_trackball_start;
uniform vec3 win_trackball_end;

// shadertoy uniforms
uniform vec3        iResolution;           // viewport resolution (in pixels)
uniform float       iGlobalTime;           // shader playback time (in seconds)
uniform vec4        iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform vec4        iDate;                 // (year, month, day, time in seconds)
//uniform sampler2D iChannel0..3;          // input channel. XX = 2D/Cube
//uniform float     iChannelTime[4];       // channel playback time (in seconds)
//uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
