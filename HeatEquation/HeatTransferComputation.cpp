//
//  HeatTransferComputation.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "HeatTransferComputation.hpp"

HeatTransferComputation::HeatTransferComputation(const Settings & settings) : settings(settings) {
    dx = settings.width / settings.N;
    dy = settings.heigh / settings.N;
    solution = MATRIX(settings.N, settings.timeIterations);
    for (int i = 0; i < settings.N; i++) {
        for (int j = 0; j < settings.N; j++) {
            solution[i][j][0] = settings.initialDistribution(i * dx, j * dy);
        }
    }
}

void HeatTransferComputation::eval() {
    
}
