#version 150  // OpenGL 2.1
in vec3 vertex;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(void) {
  gl_Position = projection * view * model * vec4(vertex, 1.0);
}