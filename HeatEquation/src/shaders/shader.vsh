#version 120  // OpenGL 2.1
attribute vec3 vertex;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(void) {
  gl_Position = projection * view * model * vec4(vertex, 1.0);
    gl_Position.z = gl_Position.z / 100;
}