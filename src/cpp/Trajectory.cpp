///
/// \file Trajectory.cpp
/// \brief
/// \author PISUPATI Phanindra
/// \date 12.04.2014
///
///
///

#include "Trajectory.h"

#include <cmath>

// --------------------------------------------------------- Constructor
Trajectory::Trajectory(uint targetNumber) :
    _targetNumber(targetNumber)
{

}

Trajectory::~Trajectory()
{
}

// --------------------------------------------------------- Public functions
uint Trajectory::size()
{
    return static_cast<uint>(_trajectory.size());
}

void Trajectory::addPoint(Point2d point)
{
    _trajectory.push_back(point);
}
Point2d Trajectory::pointAt(uint index)
{
    return _trajectory[index];
}

Point2d Trajectory::getSource()
{
    if(_trajectory.size() > 0)
        return _trajectory[0];
    else
    {
        std::cerr << "Trajectory::getSource(): trajectory is empty!" << std::endl;
        return Point2d(INFINITY, INFINITY, INFINITY);
    }
}

Point2d Trajectory::getTarget()
{
    if(_trajectory.size() > 0)
        return _trajectory[_trajectory.size() - 1];
    else
        std::cerr << "Trajectory::getSource(): Trajectory is empty!" << std::endl;
        return Point2d(INFINITY, INFINITY, INFINITY);
}

void Trajectory::makeTargetFixed(Point2d target)
{
    Point2d currentTarget = getSource();
    float deltaX = target.x - currentTarget.x;
    float deltaY = target.y - currentTarget.y;
}

void Trajectory::makeSourceFixed(Point2d source)
{
    //TODO
}

void Trajectory::rotateTrajectory(Point2d pivotPoint, float angle)
{
    //TODO
}

void Trajectory::translateTrajectory(float x, float y)
{
    //TODO
}
