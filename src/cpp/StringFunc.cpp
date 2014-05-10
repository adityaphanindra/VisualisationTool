///
/// \file StringFunc.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "StringFunc.h"
#include <iostream>

using namespace Tools;

int stringToInt(string input)
{
    int output = 0;
    stringstream ss;
    ss >> input;
    if (!(ss >> output))
    {
        cerr << "stringToUInt(): Error converting string to int!" << endl;
        output = 0;
    }
    return output;
}

unsigned int stringToUInt(string input)
{
    unsigned int output = 0;
    stringstream ss;
    ss >> input;
    if (!(ss >> output))
    {
        cerr << "stringToUInt(): Error converting string to unsigned int!" << endl;
        output = 0;
    }
	return output;
}
