#version 120  // OpenGL 2.1
attribute vec3 vertex;
void main(void) {
  gl_Position = vec4(vertex, 1.0);
}