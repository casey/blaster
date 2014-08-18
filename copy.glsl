#version 410 core

uniform sampler2D source;

//!vertex

in vec4 position;
out vec2 uv;

void main() {
  uv = position.xy * 0.5 + 0.5;
  gl_Position = position;
}

//!fragment

in vec2 uv;

layout(location = 0) out vec4 color;

void main() {
  color = texture(source, uv);
}
