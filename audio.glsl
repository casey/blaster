#version 410 core
#extension GL_ARB_shading_language_include: require
#include <common.glsl>

uniform sampler2D win_frequency;
uniform sampler2D win_waveform;
uniform sampler2D win_phaseless;

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

void main(void) {
  if (uv.y > 0.75) {
    color = texture(win_waveform, uv);
  } else if (uv.y > 0.50) {
    float y = (uv.y - 0.50) * 4;
    vec4 p = texture(win_waveform, uv);
    if (abs(y - p.r) < 0.1) color = vec4(1 - win_intensity, 1 - win_intensity, 1 - win_intensity, 1);
    else color = white;
  } else if (uv.y > 0.25) {
    color = texture(win_frequency, uv);
  } else {
    float y = (uv.y) * 4;
    vec4 p = texture(win_phaseless, uv);
    if (abs(y - p.r) < 0.1) color = white;
    else color = black;
  }
}
