///
/// \file Sequence.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Sequence.h"
#include "Settings.h"
#include <cmath>

// --------------------------------------------------------- Constructors
Sequence::Sequence(uint sequenceNumber) :
	_sequenceNumber(sequenceNumber)
{
}


// --------------------------------------------------------- Public static functions
float Sequence::getFootOrientation(vector<Marker::MarkerData> markers)
{
	return atan2(markers[FOOT_TOP].getPosition().y - markers[FOOT_BOTTOM].getPosition().y, markers[FOOT_TOP].getPosition().x - markers[FOOT_BOTTOM].getPosition().x);
}

float Sequence::getPelvisOrientation(vector<Marker::MarkerData> markers)
{
	return atan2(markers[PELVIS_RIGHT].getPosition().y - markers[PELVIS_LEFT].getPosition().y, markers[PELVIS_RIGHT].getPosition().x - markers[PELVIS_LEFT].getPosition().x) + PI;
}

vector<Marker::MarkerData> Sequence::applySmoothingFilter(vector<Marker::MarkerData> markers)
{
    //TODO
    return markers;
}

vector<Marker::MarkerData> Sequence::applyInterpolation(vector<Marker::MarkerData> markers, InterpolationType type)
{
    switch(type)
    {
    case InterpolationType::CUBIC_INTERPOLATION:
    {
        //TODO
        return markers;
    }
    default:
        cerr << "Sequence::applyInterpolation(): Interpolation Type not supported!" << std::endl;
    };

    return markers;
}

// --------------------------------------------------------- Public functions
void Sequence::ignoreFrames(uint from, uint to)
{
    if(from > to || to >= _frames.size())
    {
        cerr << "Sequence::ignoreFrames(): illegal input frame numbers, from = "
             << from << " to = " << to << std::endl;
        return;
    }
    _frames.erase(_frames.begin() + from, _frames.begin() + to);
    return;
}
