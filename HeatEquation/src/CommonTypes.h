//
//  CommonTypes.h
//  HeatEquation
//
//  Created by satori on 6/9/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef CommonTypes_h
#define CommonTypes_h
#define MATRIX(N,T) std::vector<std::vector<std::vector<double> > >(N, std::vector<std::vector<double> >(N, std::vector<double>(T,0)))
typedef std::vector<std::vector<std::vector<double> > > grid;

#endif /* CommonTypes_h */
