//
//  Renderer.hpp
//  HeatEquation
//
//  Created by satori on 6/9/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp
#include <GLFW/glfw3.h>
#include <vector>
#include "CommonTypes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Renderer {
public:
    void init(GLFWwindow * window,const grid & solution, double dx, double dy);
    void draw();
private:
    void compileShaders();
    int width;
    int height;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint program;
    GLuint attribute_vertex;
    GLfloat * vertices;
    long N;
    long M;
    long T;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    GLuint modelUniform;
    GLuint viewUniform;
    GLuint projectionUniform;
    double dx;
    double dy;
    GLuint vertexbuffer;
    GLushort * indices;
};
#endif /* Renderer_hpp */
