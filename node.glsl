#version 410 core

uniform mat4 transform;
uniform vec4 color;

//!vertex

in vec4 position;

void main() {
  gl_Position = transform * position;
}

//!fragment

layout(location = 0) out vec4 _color;

void main() {
  _color = color;
}
