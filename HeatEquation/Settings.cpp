//
//  Settings.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "Settings.hpp"
#include<cmath>
Settings::Settings(double width, double height, long N, double conductivity)
: width(width), heigh(height), N(N), conductivity(conductivity), leftBorderCondition(), rightBorderCondition(), topBorderCondition(), bottomBorderCondition() {
}

Settings::Settings() : Settings::Settings(1.0f, 1.0f, 10, 1.0f) {
}

double Settings::source(double x, double y, double T, double t) {
    return pow(t, 2.5f);
}
