#version 410 core

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
  color = vec4(uv, 1.0, 1.0);
}
