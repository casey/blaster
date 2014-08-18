#version 410 core
#extension GL_ARB_shading_language_include: require
#include <common.glsl>

uniform uint columns;
uniform uint rows;
uniform vec4 foreground;
uniform vec4 background;

uniform sampler2D font;
uniform sampler2D char;

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

void main(void) {
  vec4 raw    = texture(char, uv);
  vec2 base   = vec2(raw.r * 255/256, raw.g * 255/256);
  vec2 offset = fract(uv * vec2(columns, rows)) / 256.0;

  if (texture(font, base + offset).r == 1) {
    color = foreground * raw.b;
  } else {
    color = background * raw.a;
  }
}
