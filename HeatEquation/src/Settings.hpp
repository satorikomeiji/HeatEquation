//
//  Settings.hpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef Settings_hpp
#define Settings_hpp

#include "BorderCondition.hpp"
class Settings {
public:
    Settings(double width, double height, long N, double conductivity, double dt, long timeIterations);
    Settings();
    ~Settings();
    const double width;
    const double heigh;
    const long N;
    const double dt;
    const long timeIterations;
    const double conductivity;
    double source(double x, double y, double T, double t) const;
    double initialDistribution(double x, double y) const;
    BorderCondition leftBorderCondition;
    BorderCondition rightBorderCondition;
    BorderCondition topBorderCondition;
    BorderCondition bottomBorderCondition;
};

#endif /* Settings_hpp */
