///
/// \file Trajectory.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 12.04.2014
///

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "Settings.h"
#include "StringFunc.h"
#include "MarkerData.h"

///
/// \class Trajectory
/// \brief Trajectory Class
///
class Trajectory
{
private:
    uint                        _targetNumber;   		///< target number of nearest target
    std::vector<Point2d>        _trajectory;            ///< sequence of points (x, y and orientation)
public:
    ///
    /// \brief Constructor
    /// \param targetNumber: target number of nearest target
    ///
    Trajectory(uint targetNumber);
    ///
    /// \brief Destructor
    ///
    ~Trajectory();
    ///
    /// \brief size: returns the size of trajectory (# of frames)
    /// \return size of trajectory
    ///
    uint size();
    ///
    /// \brief addPoint
    /// \param point
    ///
    void addPoint(Point2d point);
    ///
    /// \brief pointAt: returns the point at index, if valid
    /// \param index
    /// \return point at index
    ///
    Point2d pointAt(uint index);
    ///
    /// \brief getSource: returns the first position of trajectory
    /// \return first point in trajectory
    ///
    Point2d getSource();
    ///
    /// \brief getTarget: returns the last position of trajectory
    /// \return last point in trajectory
    ///
    Point2d getTarget();
    ///
    /// \brief makeTargetFixed: rotate and translate the trajectory to make target fixed
    /// \param target: desired position and orientation of target
    ///
    void makeTargetFixed(Point2d target);
    ///
    /// \brief makeSourceFixed: rotate and translate the trajectory to make source fixed
    /// \param source: desired position and orientation of source
    ///
    void makeSourceFixed(Point2d source);
    ///
    /// \brief rotateTrajectory: rotates the trajectory about a point by a fixed angle
    /// \param pivotPoint: fixed point for rotation
    /// \param angle: angle of rotation
    ///
    void rotateTrajectory(Point2d pivotPoint, float angle);
    ///
    /// \brief translateTrajectory: translates the trajectory
    /// \param x: x translation
    /// \param y: y translation
    ///
    void translateTrajectory(float x, float y);
};


#endif
