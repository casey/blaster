#version 410 core
#extension GL_ARB_shading_language_include: require
#include <common.glsl>

//!vertex

layout(location = 0) in vec4 position;

void main(void) {
  gl_Position = position;
}

//!fragment

layout(location = 0) out vec4 _gl_FragColor;
#define gl_FragColor _gl_FragColor

SHADERTOY_BODY_GOES_HERE_LOL_BBQ
