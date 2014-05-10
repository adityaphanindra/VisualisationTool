///
/// \file Trajectory.cpp
/// \brief
/// \author PISUPATI Phanindra
/// \date 12.04.2014
///

#include "Trajectory.h"


// --------------------------------------------------------- Constructor
Trajectory::Trajectory(uint targetNumber) :
    _targetNumber(targetNumber)
{

}


// --------------------------------------------------------- Public functions
Marker::TwoDPoint Trajectory::getSource()
{
    if(_trajectory.size() > 0)
        return _trajectory[0];
    else
    {
        cerr << "Trajectory::getSource(): Trajectory is empty!" << endl;
        return Marker::TwoDPoint();
    }
}

Marker::TwoDPoint Trajectory::getTarget()
{
    if(_trajectory.size() > 0)
        return _trajectory[_trajectory.size() - 1];
    else
    {
        cerr << "Trajectory::getSource(): Trajectory is empty!" << endl;
    }

}

void Trajectory::makeTargetFixed(Marker::TwoDPoint target)
{
    Marker::TwoDPoint currentTarget = getSource();
    float deltaX = target.x - currentTarget.x;
    translateTrajectory(currentTarget.x - target.x);
}

void Trajectory::makeSourceFixed(Marker::TwoDPoint source)
{
    //TODO
}

void Trajectory::rotateTrajectory(Marker::TwoDPoint pivotPoint, float angle)
{
    //TODO
}

void Trajectory::translateTrajectory(float x, float y)
{
    //TODO
}
