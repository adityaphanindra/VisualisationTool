///
/// \file StringFunc.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///




#ifndef STRINGFUNC_H
#define STRINGFUNC_H

#include <sstream>
#include <string>

//using namespace std;

namespace StringFunc
{
///
/// \brief string to integer
/// \param input string
/// \return integer
///
int stringToInt(std::string input);

///
/// \brief string to unsigned int
/// \param input string
/// \return unsigned integer
///
unsigned int stringToUInt(std::string input);

///
/// \brief any number to string
/// \param input class
/// \return string
///
template <typename T>
std::string numToString (T num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}
} // end of namespace Tools

#endif
