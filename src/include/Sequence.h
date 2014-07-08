///
/// \file Sequence.h
/// \brief
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Settings.h"
#include "MarkerData.h"
#include "Trajectory.h"

#include <vector>
#include <map>
#include <memory>

//
/// \class Sequence
/// \brief Sequence Class
///
class Sequence
{
public:
    ///
    /// \struct Calibration Correction
    ///
    struct CalibrationCorrection
    {
        float	deltaXPelvis;
        float	deltaYPelvis;
        float	deltaYLeftFoot;
        float	deltaYRightFoot;
        float	deltaPhiPelvis;
        float	deltaPhiLeftFoot;
        float	deltaPhiRightFoot;

        CalibrationCorrection() :
            deltaXPelvis(0.0),
            deltaYPelvis(0.0),
            deltaYLeftFoot(0.0),
            deltaYRightFoot(0.0),
            deltaPhiPelvis(0.0),
            deltaPhiLeftFoot(0.0),
            deltaPhiRightFoot(0.0)
        {
        }

        std::string toString()
        {
            std::stringstream ss;
            ss << "deltaXPelvis = " << deltaXPelvis << " deltaYPelvis = " << deltaYPelvis
               << " deltaYLeftFoot = " << deltaYLeftFoot << " deltaYRightFoot = " << deltaYRightFoot
               << " deltaPhiPelvis = " << deltaPhiPelvis << " deltaPhiLeftFoot = " << deltaPhiLeftFoot
               << " deltaPhiRightFoot = " << deltaPhiRightFoot;

            return ss.str();

        }
    };

private:
    uint                                    _sequenceNumber; 		///< sequence number
    uint                                    _targetNumber;          ///< actual target number
    uint                                    _subjectNumber;         ///< subject #
    std::shared_ptr<CalibrationCorrection>  _calibrationCorrection;
    std::vector<Marker::Frame>              _frames;                ///< all markers in the sequence
    std::shared_ptr<Trajectory>             _bodyTrajectory;
    std::shared_ptr<Trajectory>             _leftFootTrajectory;
    std::shared_ptr<Trajectory>             _rightFootTrajectory;

public:
    ///
    /// \brief Constructor
    /// \param sequenceNumber: sequence number
    /// \param targetNumber: target number
    /// \param subjectNumber: subject number
    ///
    Sequence(uint sequenceNumber, uint targetNumber, uint subjectNumber);

    ///
    /// \brief get orientation from foot markers
    /// \param markers: marker data
    /// \return orientation wrt x-axis
    ///
    static float getFootOrientation(Marker::MarkerList& markers);

    ///
    /// \brief get orientation from pelvis markers
    /// \param markers: marker data
    /// \return orientation wrt x-axis
    ///
    static float getPelvisOrientation(Marker::MarkerList& markers);

    ///
    /// \brief applySmoothingFilter, applies the smoothing filter on the marker data
    /// \param markers: input markers
    /// \return output markers (smoothed)
    ///
    static Marker::MarkerList applySmoothingFilter(Marker::MarkerList& markers);

    ///
    /// \brief applyInterpolation, applies the smoothing filter on the marker data
    /// \param markers: input markers
    /// \param type: select the type of interpolation to be applied
    /// \return output markers (interpolated)
    ///
    static Marker::MarkerList applyInterpolation(Marker::MarkerList& markers, InterpolationType type);

    void calibrate(std::shared_ptr<CalibrationCorrection> calibrationCorrection);

    ///
    /// \brief ignoreFrames: ignore the frames from the sequence
    /// \param from: from frame number
    /// \param to: to frame number
    ///
    void ignoreFrames(uint from, uint to);

    void addFrames(std::vector<Marker::Frame> frames);

    void getAllTrajectories(bool recompute);

    std::shared_ptr<Trajectory> getBodyTrajectory();

    std::shared_ptr<Trajectory> getBodyTrajectory(TrajectoryType type);

private:
    inline void getPelvisMarkerList(uint frameNumber, Marker::MarkerList& pelvisMarkers);
    inline void getLeftFootMarkerList(uint frameNumber, Marker::MarkerList& leftFootMarkers);
    inline void getRightFootMarkerList(uint frameNumber, Marker::MarkerList& rightFootMarkers);
};


#endif
