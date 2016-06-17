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
#include <OpenGL/gl3.h>

void checkError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void Renderer::init(GLFWwindow *window, const grid & solution, double dx, double dy) {
    this->dx = dx;
    this->dy = dy;
    glfwGetWindowSize(window, &width, &height);
    checkError();
    glGenVertexArrays(1, &vao);
    checkError();
    glDisable(GL_CULL_FACE);
    glBindVertexArray(vao);
    checkError();
    glGenBuffers(1, &vbo);
    checkError();
    compileShaders();
    const char * attribute_name = "vertex";
    attribute_vertex = glGetAttribLocation(program, attribute_name);
    if (attribute_vertex == -1) {
        std::cerr << "Could not bind attribute " << attribute_name << std::endl;
    }
    vertices = new GLfloat [3 * solution.size() * solution[0].size() * solution[0][0].size()];
    N = solution.size();
    M = solution[0].size();
    T = solution[0][0].size();
    for (int k = 0; k < T; k++) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                vertices[3 * (k * N * M + i * M + j) + 0] = (GLfloat)(i*dx);
                vertices[3 * (k * N * M + i * M + j) + 1] = (GLfloat)(j*dy);
                vertices[3 * (k * N * M + i * M + j) + 2] = (GLfloat)solution[i][j][k];
            }
        }
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    checkError();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    checkError();
    
    modelUniform = glGetUniformLocation(program, "model");
    checkError();

    viewUniform = glGetUniformLocation(program, "view");
    checkError();

    projectionUniform = glGetUniformLocation(program, "projection");
    checkError();

    
    model = //glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0, -4.0));
    glm::rotate(glm::mat4(1.0f), (GLfloat)M_PI, glm::vec3(0.0f,0.0f,1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.0f));
    view = //glm::lookAt(glm::vec3(10.0, 10.0, 10.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4(1.0f);
    projection = //glm::perspective(70.0f, 1.0f*width/height, -3.0f, 10.0f);
    glm::mat4(1.0f);
    glUseProgram(program);
    
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));
    checkError();
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    checkError();
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
    checkError();
    glPointSize(10.0f);
    checkError();
    //glViewport(0,0,width, height);
    checkError();
    glm::vec4 result = projection * view * model
                * glm::vec4(0,0,0,1);
    glm::vec4 result1 = projection * view * model
    * glm::vec4(0,1,0,1);
//    static const GLfloat g_vertex_buffer_data[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f,  1.0f, 0.0f,
//    };
//    // This will identify our vertex buffer
//    // Generate 1 buffer, put the resulting identifier in vertexbuffer
//    glGenBuffers(1, &vertexbuffer);
//    // The following commands will talk about our 'vertexbuffer' buffer
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    // Give our vertices to OpenGL.
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    indices = new GLushort[N*M*3];
    int k = 0;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            indices[k] = i * M + j;
            indices[k+1] = (i+1)*M + j;
            indices[k+2] = i * M + j + 1;
            k+=3;
        }
    }
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    checkError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
    checkError();
    
}

void Renderer::draw() {
    glEnableVertexAttribArray(attribute_vertex);
    checkError();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_vertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    checkError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    checkError();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);
    //glDrawArrays(GL_TRIANGLES, 0, 100);
    checkError();
//    glEnableVertexAttribArray(0);
//    checkError();
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    checkError();
//    glVertexAttribPointer(
//                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//                          3,                  // size
//                          GL_FLOAT,           // type
//                          GL_FALSE,           // normalized?
//                          0,                  // stride
//                          (void*)0            // array buffer offset
//                          );
//    checkError();
//    // Draw the triangle !
//    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
//    checkError();
//    glDisableVertexAttribArray(0);
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