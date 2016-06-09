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
class Renderer {
public:
    void init(GLFWwindow * window,const grid & solution);
    void draw();
private:
    void compileShaders();
    int width;
    int height;
    GLuint vbo;
    GLuint ibo;
    GLuint program;
    GLuint attribute_vertex;
    GLfloat * vertices;
    long N;
    long M;
    long T;
};
#endif /* Renderer_hpp */
