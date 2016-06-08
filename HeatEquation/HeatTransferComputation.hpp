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
#include <vector>

#define MATRIX(N,T) std::vector<std::vector<std::vector<double> > >(N, std::vector<std::vector<double> >(N, std::vector<double>(T,0)))
typedef std::vector<std::vector<std::vector<double> > > grid;

class HeatTransferComputation {
public:
    HeatTransferComputation(const Settings & settings);
    void eval();
private:
    const Settings & settings;
    double dx;
    double dy;
    grid solution;
};
#endif /* HeatTransferComputation_hpp */
