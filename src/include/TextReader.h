///
/// \file TextReader.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 05.04.2014
///
///
///
#ifndef TEXTREADER_H
#define TEXTREADER_H

#include "Settings.h"
#include "MarkerData.h"

class TextReader
{
private:
    uint                _numMarkers;
public:
    TextReader(uint numMarkers);
    std::vector<std::map<uint, Marker::MarkerData > > readFromTxt(std::string fileName);
};

#endif // TEXTREADER_H
