#include "TextReader.h"
#include <fstream>
#include <map>

TextReader::TextReader(uint numMarkers) :
    _numMarkers(numMarkers)
{
}

std::vector<std::map<uint, Marker::MarkerData > > TextReader::readFromTxt(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::map<uint, Marker::MarkerData > > frameMarkerData;
    if(!inputFile)   {
        std::cerr << " TextReader::readFromTxt(): input file: " << fileName << " cannot be opened." << std::endl;
        return frameMarkerData;
    }

    const uint MAX_DIMENSIONS = 3;
    uint markerNumber = 0, dimension = 0;
    std::map<uint, Marker::MarkerData> currentFrame;

    // Order of reading:
    // x_1 x_2 x_3....x_(nummarkers) y_1 y_2.... etc.
    while(!inputFile.eof()) {
        float position;
        inputFile >> position;
        if(currentFrame.size() <= markerNumber)  {
            currentFrame.insert(std::make_pair(markerNumber + 1, Marker::MarkerData()));
        }
        switch(dimension)  {
        case 0:  {
            currentFrame[markerNumber + 1].setPositionX(position);
            break;
        }
        case 1: {
            currentFrame[markerNumber + 1].setPositionY(position);
            break;
        }
        case 2: {
            currentFrame[markerNumber + 1].setPositionZ(position);
            break;
        }
        default: {
            std::cerr << "TextReader::readFromTxt(): Shouldn't reach here!" << std::endl;
            exit(0);
        }
        };

        markerNumber++;
        dimension++;
        if(markerNumber == _numMarkers && dimension == MAX_DIMENSIONS) {
            frameMarkerData.push_back(currentFrame);
            currentFrame.clear();
        }
        markerNumber %= _numMarkers;
        dimension %= MAX_DIMENSIONS;
    }

    inputFile.close();
    return frameMarkerData;
}
