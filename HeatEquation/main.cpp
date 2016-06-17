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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    Settings settings(1.0, 1.0, 999, 0.1, 0.0001, 100);
    settings.leftBorderCondition.B = 1.0f;
    settings.leftBorderCondition.phi = 0.0f;
    settings.rightBorderCondition.B = 1.0f;
    settings.rightBorderCondition.phi = 0.0f;
    settings.topBorderCondition.A = 1.0f;
    settings.topBorderCondition.phi = 0.0f;
    settings.bottomBorderCondition.A = 1.0f;
    settings.bottomBorderCondition.phi = 0.0f;
    HeatTransferComputation computation(settings);
    clock_t begin_time = clock();
    computation.eval();
    std::cout << "Unparallel time " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
    begin_time = clock();
    computation.parallelEval();
    std::cout << "Parallel time " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<std::endl;
    //computation.outputSolution();
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    computation.prepareForDrawing(window);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1);
        computation.draw();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
