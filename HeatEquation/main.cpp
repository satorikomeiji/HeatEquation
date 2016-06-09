//
//  main.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include <iostream>
#include "Settings.hpp"
#include "HeatTransferComputation.hpp"
#include <GLFW/glfw3.h>
int main(int argc, const char * argv[]) {
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    Settings settings;
    settings.leftBorderCondition.B = 1.0f;
    settings.leftBorderCondition.phi = 0.0f;
    settings.rightBorderCondition.B = 1.0f;
    settings.rightBorderCondition.phi = 0.0f;
    settings.topBorderCondition.A = 1.0f;
    settings.topBorderCondition.phi = 0.0f;
    settings.bottomBorderCondition.A = 1.0f;
    settings.bottomBorderCondition.phi = 0.0f;
    HeatTransferComputation computation(settings);
    computation.eval();
    computation.outputSolution();
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    computation.prepareForDrawing(window);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        computation.draw();
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
