///
/// \file StringFunc.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "StringFunc.h"
#include <iostream>


int stringToInt(std::string input) {
    int output = 0;
    std::stringstream ss;
    ss >> input;
    if (!(ss >> output)) {
        std::cerr << "stringToUInt(): Error converting string to int!" << std::endl;
        output = 0;
    }
    return output;
}

unsigned int stringToUInt(std::string input) {
    unsigned int output = 0;
    std::stringstream ss;
    ss >> input;
    if (!(ss >> output)) {
        std::cerr << "stringToUInt(): Error converting string to unsigned int!" << std::endl;
        output = 0;
    }
	return output;
}
