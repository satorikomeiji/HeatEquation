//
//  HeatTransferComputation.hpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef HeatTransferComputation_hpp
#define HeatTransferComputation_hpp
#include "Settings.hpp"
#include <vector>
#include <GLFW/glfw3.h>
#include "CommonTypes.h"
#include "Renderer.hpp"



class HeatTransferComputation {
public:
    HeatTransferComputation(const Settings & settings);
    void eval();
    void outputSolution();
    void prepareForDrawing(GLFWwindow * window);
    void draw();
private:
    const Settings & settings;
    double dx;
    double dy;
    grid solution;
    Renderer renderer;
};
#endif /* HeatTransferComputation_hpp */
