//
//  Utils.hpp
//  HeatEquation
//
//  Created by satori on 6/9/16.
//  Copyright © 2016 rinnex. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp
#include <fstream>
#include <string>

class Utils {
public:
    static inline std::string readFile(const char * filename) {
        std::ifstream file(filename);
        std::string str;
        std::string file_contents;
        while (std::getline(file, str))
        {
            file_contents += str;
            file_contents.push_back('\n');
        }
        return file_contents;
    }
};
#endif /* Utils_hpp */
