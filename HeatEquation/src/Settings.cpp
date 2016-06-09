//
//  Settings.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "Settings.hpp"
#include<cmath>
Settings::Settings(double width, double height, long N, double conductivity, double dt, long timeIterations)
: width(width), heigh(height), N(N), conductivity(conductivity), leftBorderCondition(), rightBorderCondition(), topBorderCondition(), bottomBorderCondition(), dt(dt), timeIterations(timeIterations) {
}

Settings::~Settings() {
}

Settings::Settings() : Settings::Settings(1.0f, 1.0f, 100, 0.01f, 0.001, 100) {
}

double Settings::source(double x, double y, double T, double t) const {
    return 1000 * (T-T*T*T);
}

double Settings::initialDistribution(double x, double y) const {
    return sin(x * M_PI) * sin(y * M_PI);
}
