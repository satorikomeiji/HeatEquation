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
    
}
