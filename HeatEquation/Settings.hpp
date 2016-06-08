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
    Settings(double width, double height, long N, double conductivity);
    Settings();
    ~Settings();
    const double width;
    const double heigh;
    const long N;
    const double conductivity;
    double source(double x, double y, double T, double t);
    BorderCondition leftBorderCondition;
    BorderCondition rightBorderCondition;
    BorderCondition topBorderCondition;
    BorderCondition bottomBorderCondition;
};

#endif /* Settings_hpp */
