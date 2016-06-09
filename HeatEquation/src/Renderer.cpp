//
//  Renderer.cpp
//  HeatEquation
//
//  Created by satori on 6/9/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "Renderer.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "Utils.hpp"
#include <glm/gtc/type_ptr.hpp>
//#include <OpenGL/gl.h>

void checkError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void Renderer::init(GLFWwindow *window, const grid & solution) {
    glfwGetWindowSize(window, &width, &height);
    glGenBuffers(1, &vbo);
    compileShaders();
    const char * attribute_name = "vertex";
    attribute_vertex = glGetAttribLocation(program, attribute_name);
    if (attribute_vertex == -1) {
        std::cerr << "Could not bind attribute " << attribute_name << std::endl;
    }
    vertices = new GLfloat [solution.size() * solution[0].size() * solution[0][0].size()];
    N = solution.size();
    M = solution[0].size();
    T = solution[0][0].size();
    for (int k = 0; k < T; k++) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                vertices[k * N * M + i * M + j] = solution[i][j][k];
            }
        }
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    checkError();
    
    modelUniform = glGetUniformLocation(program, "model");
    checkError();

    viewUniform = glGetUniformLocation(program, "view");
    checkError();

    projectionUniform = glGetUniformLocation(program, "projection");
    checkError();

    
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0, -4.0));
    view = glm::lookAt(glm::vec3(10.0, 10.0, 10.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(45.0f, 1.0f*width/height, -10.0f, 10.0f);
    glUseProgram(program);
    
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));
    checkError();
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    checkError();
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
    checkError();
    glPointSize(10.0f);
    checkError();
    glViewport(0,0,width, height);
    checkError();
    glm::vec4 result = projection * view * model
                * glm::vec4(0,0,0,1);
}

void Renderer::draw() {
    glEnableVertexAttribArray(attribute_vertex);
    checkError();
    glVertexAttribPointer(attribute_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    checkError();
    glDrawArrays(GL_TRIANGLES, 0, N * M);
    checkError();
}



void Renderer::compileShaders() {
    std::string vertexSource = Utils::readFile("shader.vsh");
    std::string fragmentSource = Utils::readFile("shader.fsh");
    
    //Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //Send the vertex shader source code to GL
    //Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    
    //Compile the vertex shader
    glCompileShader(vertexShader);
    
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        
        //We don't need the shader anymore.
        glDeleteShader(vertexShader);
        
        //Use the infoLog as you see fit.
        
        //In this simple program, we'll just leave
        return;
    }
    
    //Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Send the fragment shader source code to GL
    //Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    
    //Compile the fragment shader
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        
        //We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        //Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);
        
        //Use the infoLog as you see fit.
        
        //In this simple program, we'll just leave
        return;
    }
    
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.
    program = glCreateProgram();
    
    //Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    //Link our program
    glLinkProgram(program);
    
    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        
        //We don't need the program anymore.
        glDeleteProgram(program);
        //Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        //Use the infoLog as you see fit.
        
        //In this simple program, we'll just leave
        return;
    }
    
    //Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
}