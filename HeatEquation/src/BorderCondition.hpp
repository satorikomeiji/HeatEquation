//
//  BorderCondition.hpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef BorderCondition_hpp
#define BorderCondition_hpp

class BorderCondition {
public:
    BorderCondition(double A, double B, double phi);
    BorderCondition();
    const double A;
    const double B;
    const double phi;
    double borderFunc(double t) const;
};
#endif /* BorderCondition_hpp */
