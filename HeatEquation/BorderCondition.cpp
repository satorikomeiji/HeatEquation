//
//  BorderCondition.cpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#include "BorderCondition.hpp"

BorderCondition::BorderCondition(double A, double B, double phi) : A(A), B(B), phi(phi) {
}

BorderCondition::BorderCondition() : A(0.0f), B(0.0f), phi(0.0f) {
}

double BorderCondition::borderFunc(double t) {
    return phi;
}
