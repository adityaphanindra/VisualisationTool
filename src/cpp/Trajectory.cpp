///
/// \file Trajectory.cpp
/// \brief
/// \author PISUPATI Phanindra
/// \date 12.04.2014
///
///
///

#include "Trajectory.h"
#include "Tools.h"

#include <cmath>

// --------------------------------------------------------- Constructor
Trajectory::Trajectory(uint targetNumber) :
    _targetNumber(targetNumber)
{

}

Trajectory::Trajectory(const Trajectory & copy) :
    _targetNumber(copy._targetNumber),
    _trajectory(copy._trajectory)
{

}

Trajectory::~Trajectory() {
}

// --------------------------------------------------------- Public functions
uint Trajectory::size() {
    return static_cast<uint>(_trajectory.size());
}

void Trajectory::addPoint(Point2d point) {
    _trajectory.push_back(point);
}
Point2d Trajectory::pointAt(uint index) {
    return _trajectory[index];
}

Point2d Trajectory::getSource() {
    if(_trajectory.size() > 0)
        return _trajectory[0];
    else {
        std::cerr << "Trajectory::getSource(): trajectory is empty!" << std::endl;
        return Point2d(INFINITY, INFINITY, INFINITY);
    }
}

Point2d Trajectory::getTarget() {
    if(_trajectory.size() > 0)
        return _trajectory[_trajectory.size() - 1];
    else
        std::cerr << "Trajectory::getSource(): Trajectory is empty!" << std::endl;
        return Point2d(INFINITY, INFINITY, INFINITY);
}

void Trajectory::makeTargetFixed(Point2d target) {
    Point2d currentTarget = getTarget();
    float deltaX = target.x - currentTarget.x;
    float deltaY = target.y - currentTarget.y;
    float deltaPhi = target.orientation - currentTarget.orientation;
    translateTrajectory(deltaX, deltaY);
    rotateTrajectory(target, deltaPhi);
}

void Trajectory::makeSourceFixed(Point2d source) {
    //TODO
    Point2d currentSource = getSource();
    float deltaX = source.x - currentSource.x;
    float deltaY = source.y - currentSource.y;
    float deltaPhi = source.orientation - currentSource.orientation;
    translateTrajectory(deltaX, deltaY);
    rotateTrajectory(source, deltaPhi);
}

void Trajectory::rotateTrajectory(Point2d, float angle) {
    //TODO
    for(Point2d & point : _trajectory) {
        point = Tools::rotatePoint(point, angle);
    }
}

void Trajectory::translateTrajectory(float x, float y) {
    //TODO
    for(Point2d & point : _trajectory) {
        point = Tools::translatePoint(point, x, y);
    }
}
