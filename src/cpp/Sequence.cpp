///
/// \file Sequence.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Sequence.h"
#include "Settings.h"
#include "Tools.h"

#include <cmath>

// --------------------------------------------------------- Constructors
Sequence::Sequence(uint sequenceNumber, uint targetNumber, uint subjectNumber) :
    _sequenceNumber(sequenceNumber),
    _targetNumber(targetNumber),
    _subjectNumber(subjectNumber),
    _calibrationCorrection(std::shared_ptr<CalibrationCorrection>(new CalibrationCorrection())),
    _bodyTrajectory(std::shared_ptr<Trajectory>(new Trajectory(targetNumber))),
    _leftFootTrajectory(std::shared_ptr<Trajectory>(new Trajectory(targetNumber))),
    _rightFootTrajectory(std::shared_ptr<Trajectory>(new Trajectory(targetNumber)))
{
}


// --------------------------------------------------------- Public static functions
float Sequence::getFootOrientation(Marker::MarkerList& markers) {
    return atan2(markers[FOOT_TOP].getPosition().y - markers[FOOT_BOTTOM].getPosition().y, markers[FOOT_TOP].getPosition().x - markers[FOOT_BOTTOM].getPosition().x);
}

float Sequence::getPelvisOrientation(Marker::MarkerList& markers) {
    return atan2(markers[PELVIS_RIGHT].getPosition().y - markers[PELVIS_LEFT].getPosition().y, markers[PELVIS_RIGHT].getPosition().x - markers[PELVIS_LEFT].getPosition().x) + PI;
}

Marker::MarkerList Sequence::applySmoothingFilter(Marker::MarkerList& markers) {
    //TODO
    return markers;
}

Marker::MarkerList Sequence::applyInterpolation(Marker::MarkerList& markers, InterpolationType type) {
    switch(type)  {
    case InterpolationType::CUBIC_INTERPOLATION:  {
        //TODO
        return markers;
    }
    default:
        std::cerr << "Sequence::applyInterpolation(): Interpolation Type not supported!" << std::endl;
    };

    return markers;
}

// --------------------------------------------------------- Public functions
void Sequence::calibrate(std::shared_ptr<CalibrationCorrection> calibrationCorrection) {
    _calibrationCorrection = calibrationCorrection;
}

void Sequence::ignoreFrames(uint from, uint to) {
    if(from > to || to >= _frames.size()) {
        std::cerr << "Sequence::ignoreFrames(): illegal input frame numbers, from = "
             << from << " to = " << to << std::endl;
        return;
    }
    _frames.erase(_frames.begin() + from, _frames.begin() + to);
    return;
}

void Sequence::addFrames(std::vector<Marker::Frame> frames) {
    if(_frames.size() != 0)  {
        std::cout << "Sequence::addFrames(): Sequence: " << _sequenceNumber
                  << " already contains frames, so, appending frames." << std::endl;
    }

    _frames.insert(_frames.end(), frames.begin(), frames.end());
}

void Sequence::getAllTrajectories(bool recompute) {
    if(recompute) {
        for(uint frameNumber = 0; frameNumber < _frames.size(); frameNumber++)  {
            std::unique_ptr<Marker::MarkerList> pelvisMarkers = std::unique_ptr<Marker::MarkerList>(new Marker::MarkerList());
            getPelvisMarkerList(frameNumber, *pelvisMarkers);
            Marker::Position centre = Marker::getCentre(*pelvisMarkers);
            float orientation = getPelvisOrientation(*pelvisMarkers);
            Point2d bodyPosition(centre.x, centre.y, orientation);
            bodyPosition = Tools::rotatePoint(bodyPosition, _calibrationCorrection->deltaPhiPelvis);
            bodyPosition = Tools::translatePoint(bodyPosition, _calibrationCorrection->deltaXPelvis, _calibrationCorrection->deltaYPelvis);
            _bodyTrajectory->addPoint(bodyPosition);

            std::unique_ptr<Marker::MarkerList> leftFootMarkers = std::unique_ptr<Marker::MarkerList>(new Marker::MarkerList());
            getLeftFootMarkerList(frameNumber, *leftFootMarkers);
            centre = Marker::getCentre(*leftFootMarkers);
            orientation = getFootOrientation(*leftFootMarkers);
            Point2d leftFootPosition(centre.x, centre.y, orientation);
            leftFootPosition = Tools::rotatePoint(leftFootPosition, _calibrationCorrection->deltaPhiLeftFoot);
            leftFootPosition = Tools::translatePoint(leftFootPosition, 0, _calibrationCorrection->deltaYLeftFoot);
            _leftFootTrajectory->addPoint(leftFootPosition);

            std::unique_ptr<Marker::MarkerList> rightFootMarkers = std::unique_ptr<Marker::MarkerList>(new Marker::MarkerList());
            getRightFootMarkerList(frameNumber, *rightFootMarkers);
            centre = Marker::getCentre(*rightFootMarkers);
            orientation = getFootOrientation(*rightFootMarkers);
            Point2d rightFootPosition(centre.x, centre.y, orientation);
            rightFootPosition = Tools::rotatePoint(rightFootPosition, _calibrationCorrection->deltaPhiRightFoot);
            rightFootPosition = Tools::translatePoint(rightFootPosition, 0, _calibrationCorrection->deltaYRightFoot);
            _rightFootTrajectory->addPoint(rightFootPosition);
        }
        if(DEBUG)
            std::cout << "Sequence::getAllTrajectories(): Trajectories computed for subject: "
                      << _subjectNumber << " sequence: " << _sequenceNumber << " computed." << std::endl;
    }
    else   {
        //TODO
    }
}

std::shared_ptr<Trajectory> Sequence::getBodyTrajectory() {
    return _bodyTrajectory;
}

// --------------------------------------------------------- Private functions
inline void Sequence::getPelvisMarkerList(uint frameNumber, Marker::MarkerList& pelvisMarkers) {
    for(uint markerNumber = AllMarkers::PELVIS_LEFT_MARKER; markerNumber <= AllMarkers::PELVIS_RIGHT_MARKER; markerNumber++)
    {
        pelvisMarkers.push_back(_frames[frameNumber][markerNumber]);
    }
}

inline void Sequence::getLeftFootMarkerList(uint frameNumber, Marker::MarkerList& leftFootMarkers) {
    for(uint markerNumber = AllMarkers::LEFT_LEFT_MARKER; markerNumber <= AllMarkers::LEFT_RIGHT_MARKER; markerNumber++)    {
        leftFootMarkers.push_back(_frames[frameNumber][markerNumber]);
    }
}

inline void Sequence::getRightFootMarkerList(uint frameNumber, Marker::MarkerList& rightFootMarkers) {
    for(uint markerNumber = AllMarkers::RIGHT_LEFT_MARKER; markerNumber <= AllMarkers::RIGHT_RIGHT_MARKER; markerNumber++)    {
        rightFootMarkers.push_back(_frames[frameNumber][markerNumber]);
    }
}
