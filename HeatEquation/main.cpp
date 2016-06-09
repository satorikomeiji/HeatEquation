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
int main(int argc, const char * argv[]) {
    
    
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
    
    return 0;
}
