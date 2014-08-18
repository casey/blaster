#version 410 core
#extension GL_ARB_shading_language_include: require
#include <common.glsl>

//!vertex

layout(location = 0) in vec4 position;
out vec2 uv;

void main(void) {
  uv = position.xy * 0.5 + 0.5;
  gl_Position = position;
}

//!fragment

in vec2 uv;
layout(location = 0) out vec4 color;

float d_quarter(vec3 p) {
  return max(-p.x, -p.z);
}

vec3 rotate_vector(vec4 quat, vec3 vec) {
  return vec + 2.0 * cross( cross( vec, quat.xyz ) + quat.w * vec, quat.xyz );
}

vec4 quat_from_aa(vec3 v, float angle) {
	float s = sin(angle * 0.5);
  return vec4( 
    v.x * s,
    v.y * s,
    v.z * s,
    cos(angle * 0.5)
  );
}

float df(vec3 _) {
  vec3  rotation_axis = normalize(vec3(-1, 1, 0));
  float angle         = win_elapsed;
  vec4  q             = quat_from_aa(rotation_axis, angle);
  vec3  v             = normalize(vec3(1, 1, 0)) * 1.40;
  vec3 rotated        = rotate_vector(q, v);

  vec3 p = op_repeat(_, 3);

  return //op_u(
    d_cube(p, 0.5)
    //op_sub(d_sphere(p), d_quarter(p)),
    //d_sphere(p, 0.4 * (1 + win_intensity)),
    //op_u(
      //d_sphere(p - rotated, 0.2 + win_intensity * 0.2),
      //d_cube(p + rotated, 0.2 + win_intensity * 0.2))
  ;//);
}

vec3 sat(vec3 c, float factor) {
  float p = sqrt(c.r * c.r * .299+ c.g * c.g * .587 + c.b * c.b * .114);
  return vec3(
    p + (c.r - p) * factor,
    p + (c.g - p) * factor,
    p + (c.b - p) * factor
  );
}

void main(void) {
  march_cam_t cam       = march_cam(win_fps, vec3(0, 0, 0), win_aspect_ratio, uv);
	float       dist      = 0.02;
	float       t         = 0.5;
	float       max_depth = 12.0;
  float       delta     = 0.001;
	vec3        pos       = vec3(0);
	
	for (int i = 0; i < 180; i++) {
		pos = cam.origin + cam.ray * t;
		dist = df(pos);
		t += dist;
    if (abs(dist) < delta || t > max_depth) break;
	}

  float l = length(pos);

  if (t > max_depth) {
    if (win_beat % 3 == 0) discard;
    if (win_beat % 3 == 1) return;
    if (win_beat % 3 == 2);
  }
	
	vec3 small  = vec3(delta, 0, 0);
	vec3 normal = vec3(dist - df(pos - small.xyy), dist - df(pos - small.yxy), dist - df(pos - small.yyx));
	normal = normalize(normal);

  l *= 0.2 - win_intensity;

  vec3 diffuse  = l > 1.10 ? vec3(0.9,   0.8,   0.7  ) :
                  l > 1.00 ? vec3(0.200, 0.400, 0.600) :
                  l > 0.97 ? vec3(0.180, 0.749, 0.855) :
                  l > 0.90 ? vec3(0.576, 0.239, 0.102) :
                  l > 0.75 ? vec3(0.894, 0.353, 0.110) :
                  l > (0.401 * (1 + win_intensity)) ? vec3(0.984, 0.671, 0.322) :
                              vec3(0.992, 0.945, 0.510) ;

  diffuse = sat(diffuse, 1.25);

  vec3  light_pos   = vec3(25, 25, 0);
  vec3  light_dir   = normalize(light_pos - pos);
  vec3  reflect_dir = reflect(-light_dir, normal);
  vec3  view_dir    = normalize(-pos);
  float lambertian  = max(dot(light_dir, normal), 0.0);
  float specular    = 0.0;

  if(lambertian > 0.0) {
    float spec_angle = max(dot(reflect_dir, view_dir), 0.0);
    specular = pow(spec_angle, 8.0);
  }

  vec3 specular_color = vec3(white) * 0.2;

  color = vec4(diffuse * 0.5 + lambertian * diffuse + specular * specular_color, 1.0);
}
