#version 300 es
layout(location = 0) in vec2 inPosition;

uniform vec4 color;
uniform float scale;
uniform vec2 translation;

void main() {
  gl_PointSize = 2.0;

  vec2 newPosition = inPosition * scale;
  gl_Position = vec4(inPosition, 0, 1);
}