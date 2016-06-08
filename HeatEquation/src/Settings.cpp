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

Settings::Settings() : Settings::Settings(1.0f, 1.0f, 100, 1.0f, 0.2, 100) {
}

double Settings::source(double x, double y, double T, double t) const {
    return 1/((0.5-x) * (0.5-x) + (0.5-y) * (0.5-y)) * pow(t, 2.5f);
}

double Settings::initialDistribution(double x, double y) const {
    return 10;
}
