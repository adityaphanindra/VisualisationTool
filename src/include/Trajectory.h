///
/// \file Trajectory.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 12.04.2014
///

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Settings.h"
#include "StringFunc.h"
#include "MarkerData.h"

using namespace std;

///
/// \class Trajectory
/// \brief Trajectory Class
///
class Trajectory
{
private:
    uint                        _targetNumber;   		///< target number of nearest target
    vector<Marker::TwoDPoint>   _trajectory;            ///< sequence of points

    ///
    /// \brief Constructor
    /// \param targetNumber: target number of nearest target
    ///
    Trajectory(uint targetNumber);
    ///
    /// \brief getSource: returns the first position of trajectory
    /// \return first point in trajectory
    ///
    Marker::TwoDPoint getSource();
    ///
    /// \brief getTarget: returns the last position of trajectory
    /// \return last point in trajectory
    ///
    Marker::TwoDPoint getTarget();
    ///
    /// \brief makeTargetFixed: rotate and translate the trajectory to make target fixed
    /// \param target: desired position and orientation of target
    ///
    void makeTargetFixed(Marker::TwoDPoint target);
    ///
    /// \brief makeSourceFixed: rotate and translate the trajectory to make source fixed
    /// \param source: desired position and orientation of source
    ///
    void makeSourceFixed(Marker::TwoDPoint source);
    ///
    /// \brief rotateTrajectory: rotates the trajectory about a point by a fixed angle
    /// \param pivotPoint: fixed point for rotation
    /// \param angle: angle of rotation
    ///
    void rotateTrajectory(Marker::TwoDPoint pivotPoint, float angle);
    ///
    /// \brief translateTrajectory: translates the trajectory
    /// \param x: x translation
    /// \param y: y translation
    ///
    void translateTrajectory(float x, float y);
};


#endif
