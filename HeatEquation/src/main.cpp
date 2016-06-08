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
    HeatTransferComputation computation(settings);
    computation.eval();
    computation.outputSolution();
    
    return 0;
}
