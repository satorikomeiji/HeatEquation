//
//  HeatTransferComputation.hpp
//  HeatEquation
//
//  Created by satori on 6/8/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef HeatTransferComputation_hpp
#define HeatTransferComputation_hpp
#include "Settings.hpp"
class HeatTransferComputation {
public:
    HeatTransferComputation(const Settings & settings);
private:
    const Settings & settings;
    double dx;
    double dy;
};
#endif /* HeatTransferComputation_hpp */
