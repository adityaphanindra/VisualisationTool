///
/// \file Subject.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Subject.h"
#include "C3DReader.h"
#include "StringFunc.h"
#include "Sequence.h"
#include "TextReader.h"
#include "Targets.h"

#include <iostream>
#include <fstream>
#include <QDir>
#include <QString>


// --------------------------------------------------------- Constructors
Subject::Subject(uint subjectNumber, std::shared_ptr<Targets> targets) :
    _subjectNumber(subjectNumber),
    _c3dDirectory("..//data//c3d//" + StringFunc::numToString(subjectNumber)),
    _saveDirectory("..//data//save//"),
    _txtDirectory("..//data//txt//" + StringFunc::numToString(subjectNumber)),
    _calibrationCorrection(std::shared_ptr<Sequence::CalibrationCorrection>(new Sequence::CalibrationCorrection())),
    _targets(targets)
{
    for(uint sequenceNumber = 1; sequenceNumber <= NUM_SEQUENCES; sequenceNumber++)
    {
        uint targetNumber = _targets->getTargetNumber(_subjectNumber, sequenceNumber);
        _sequences.push_back(std::unique_ptr<Sequence>(new Sequence(sequenceNumber, targetNumber, _subjectNumber)));
    }
    if(DEBUG)
    {
        std::cout << "Subject::Subject(): Subject: " << _subjectNumber << " intialised." << std::endl;
    }
}

// --------------------------------------------------------- Public Functions
void Subject::setThresholds(Subject::Thresholds thresholds)
{
    _thresholds = thresholds;

    if(DEBUG)
    {
        std::cout << "Subject::setThresholds(): subject #" << _subjectNumber << " thresholds set to: " << thresholds.toString() << std::endl;
    }
}

void Subject::calibrate()
{
    std::string bCalibFileName = _c3dDirectory + "//Body.c3d";
    std::string lCalibFileName = _c3dDirectory + "//Left.c3d";
    std::string rCalibFileName = _c3dDirectory + "//Right.c3d";

    C3D::C3DReader reader(NUM_MARKERS, FRAME_RATE);
    std::vector<Marker::Frame > bodyCalib = reader.readAllFrames(bCalibFileName); // rest position marker data (all markers)
    std::vector<Marker::Frame > leftFootCalib = reader.readAllFrames(lCalibFileName); // left foot marker data
    std::vector<Marker::Frame > rightFootCalib = reader.readAllFrames(rCalibFileName); // right foot marker data

    Marker::Position pelvisCentre, leftFootCentre, rightFootCentre;

    Marker::MarkerList pelvisMarkers;
    Marker::MarkerList leftFootMarkers;
    Marker::MarkerList rightFootMarkers;
    if(bodyCalib.size() == 1)
    {
        for(auto it = bodyCalib[0].begin(); it != bodyCalib[0].end(); it++)
        {
            if(it->first == static_cast<uint>(PELVIS_LEFT_MARKER) || it->first == static_cast<uint>(PELVIS_RIGHT_MARKER))
                pelvisMarkers.push_back(it->second);
            else if(it->first >= static_cast<uint>(LEFT_LEFT_MARKER) && it->first <= static_cast<uint>(LEFT_BOTTOM_MARKER))
                leftFootMarkers.push_back(it->second);
            else if(it->first >= static_cast<uint>(RIGHT_LEFT_MARKER) && it->first <= static_cast<uint>(RIGHT_BOTTOM_MARKER))
                rightFootMarkers.push_back(it->second);
        }
    }
    else
    {
        std::cerr << "Subject::calibrate(): invalid pelvis calibration file!" << std::endl;
    }
    pelvisCentre = Marker::getCentre(pelvisMarkers);
    leftFootCentre = Marker::getCentre(leftFootMarkers);
    rightFootCentre = Marker::getCentre(rightFootMarkers);

    // X, Y- correction of pelvis
    _calibrationCorrection->deltaXPelvis = -pelvisCentre.x;
    _calibrationCorrection->deltaYPelvis = -pelvisCentre.y;
    // Correction in orientation of pelvis
    _calibrationCorrection->deltaPhiPelvis = (PI / 2.0) - Sequence::getPelvisOrientation(pelvisMarkers);
    // Y-correction for feet
    _calibrationCorrection->deltaYLeftFoot = -leftFootCentre.y;
    _calibrationCorrection->deltaYRightFoot = -rightFootCentre.y;

    // compute corrections for orientations of feet from feet calibration files
    leftFootMarkers.clear();
    rightFootMarkers.clear();

    if(leftFootCalib.size() == 1)
    {
        for(auto it = leftFootCalib[0].begin(); it != leftFootCalib[0].end(); it++)
        {
            leftFootMarkers.push_back(it->second);
        }
    }
    else
    {
        std::cerr << "Subject::calibrate(): invalid left foot calibration file!" << std::endl;
    }
    if(rightFootCalib.size() == 1)
    {
        for(auto it = rightFootCalib[0].begin(); it != rightFootCalib[0].end(); it++)
        {
            rightFootMarkers.push_back(it->second);
        }
    }
    else
    {
        std::cerr << "Subject::calibrate(): invalid right foot calibration file!" << std::endl;
    }

    // compute the orientation error for left and right feet
    _calibrationCorrection->deltaPhiLeftFoot = (PI / 2.0) - Sequence::getFootOrientation(leftFootMarkers);
    _calibrationCorrection->deltaPhiRightFoot = (PI / 2.0) - Sequence::getFootOrientation(rightFootMarkers);

    for(uint sequenceNumber = 0; sequenceNumber < _sequences.size(); sequenceNumber++)
        _sequences[sequenceNumber]->calibrate(_calibrationCorrection);

    if(DEBUG)
    {
        std::cout << "Subject::calibrate(): subject #" << _subjectNumber << " calibrated" << std::endl;
    }
    saveCalibration();
}

inline void Subject::saveCalibration()
{
    if(!QDir(_saveDirectory.c_str()).exists())
    {
        QDir dir;
        dir.mkpath(_saveDirectory.c_str());
    }
    std::string calibCorrectionFileName = _saveDirectory + "calib_correction_" + StringFunc::numToString(_subjectNumber);
    std::ofstream fCalib(calibCorrectionFileName);
    fCalib << _calibrationCorrection->toString() << std::endl;
    std::cout << "Subject::saveCalibration(): Saving file: " << calibCorrectionFileName << std::endl;
    fCalib.close();
}

void Subject::initialiseAllSequences()
{
    std::unique_ptr<TextReader> textReader = std::unique_ptr<TextReader>(new TextReader(NUM_MARKERS));
    for(uint sequenceNumber = 1; sequenceNumber <= _sequences.size(); sequenceNumber++)
    {
        std::string sequenceFileName = _txtDirectory + "//" + StringFunc::numToString(sequenceNumber) + ".txt";
        std::vector<Marker::Frame> frames = textReader->readFromTxt(sequenceFileName);
        _sequences[sequenceNumber - 1]->addFrames(frames);
        if(DEBUG)
            std::cout << "Subject::initialiseAllSequences(): Subject: " << _subjectNumber
                      << " Sequence: " << sequenceNumber << " initialised." << std::endl;
    }
}

void Subject::initialiseSequence(TextReader& textReader, uint sequenceNumber)
{
    if(sequenceNumber > _sequences.size())
    {
        std::cerr << "Subject::intialiseSequence(): Invalid sequence number: " << sequenceNumber << std::endl;
        return;
    }
    std::string sequenceFileName = _txtDirectory + "//" + StringFunc::numToString(sequenceNumber) + ".txt";
    std::vector<Marker::Frame> frames = textReader.readFromTxt(sequenceFileName); // read smoothed processed markers from text file
    _sequences[sequenceNumber - 1]->addFrames(frames); // add all read frames to sequence object

    if(DEBUG)
        std::cout << "Subject::initialiseSequence(): Subject: " << _subjectNumber
                  << " Sequence: " << sequenceNumber << " initialised." << std::endl;
}

void Subject::computeTrajectories(uint sequenceNumber)
{
    bool recompute = true;
    _sequences[sequenceNumber - 1]->getAllTrajectories(recompute);
}

std::shared_ptr<Trajectory> Subject::getTrajectory(uint sequenceNumber)
{
    return _sequences[sequenceNumber - 1]->getBodyTrajectory();
}

