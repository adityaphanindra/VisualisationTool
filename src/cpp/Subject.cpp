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

#include <iostream>

using namespace std;
using Marker::MarkerData;
using Marker::Position;

// --------------------------------------------------------- Constructors
Subject::Subject(uint subjectNumber) :
	_subjectNumber(subjectNumber)
{
    _c3dDirectory = "..//data//c3d//" + Tools::numToString(subjectNumber);
    if(DEBUG)
    {
        cout << "Subject::Subject(): subject #" << _subjectNumber << endl;
    }
}

// --------------------------------------------------------- Public Functions
void Subject::setThresholds(Subject::Thresholds thresholds)
{
	_thresholds = thresholds;

    if(DEBUG)
    {
        cout << "Subject::setThresholds(): subject #" << _subjectNumber << " thresholds set to: " << thresholds.toString() << endl;
    }
}

void Subject::calibrate()
{
    string bCalibFileName = _c3dDirectory + "//Body.c3d";
	string lCalibFileName = _c3dDirectory + "//Left.c3d";
	string rCalibFileName = _c3dDirectory + "//Right.c3d";
	
	C3D::C3DReader reader(NUM_MARKERS, FRAME_RATE);
    vector<map<uint, MarkerData > > bodyCalib = reader.readAllFrames(bCalibFileName); // rest position marker data (all markers)
    vector<map<uint, MarkerData > > leftFootCalib = reader.readAllFrames(lCalibFileName); // left foot marker data
    vector<map<uint, MarkerData > > rightFootCalib = reader.readAllFrames(rCalibFileName); // right foot marker data

    Position pelvisCentre, leftFootCentre, rightFootCentre;

    vector<MarkerData> pelvisMarkers;
    vector<MarkerData> leftFootMarkers;
    vector<MarkerData> rightFootMarkers;
    if(bodyCalib.size() == 1)
    {
        for(auto it = bodyCalib[0].begin(); it != bodyCalib[0].end(); it++)
        {
            if(it->first == uint(PELVIS_LEFT_MARKER) || it->first == uint(PELVIS_RIGHT_MARKER))
                pelvisMarkers.push_back(it->second);
            else if(it->first >= uint(LEFT_LEFT_MARKER) && it->first <= uint(LEFT_BOTTOM_MARKER))
                leftFootMarkers.push_back(it->second);
            else if(it->first >= uint(RIGHT_LEFT_MARKER) && it->first <= uint(RIGHT_BOTTOM_MARKER))
                rightFootMarkers.push_back(it->second);
        }
    }
    else
    {
        cerr << "Subject::calibrate(): invalid pelvis calibration file!" << endl;
    }
    pelvisCentre = Marker::getCentre(pelvisMarkers);
    leftFootCentre = Marker::getCentre(leftFootMarkers);
    rightFootCentre = Marker::getCentre(rightFootMarkers);

    // X, Y- correction of pelvis
    _calibrationCorrection.deltaXPelvis = -pelvisCentre.x;
    _calibrationCorrection.deltaYPelvis = -pelvisCentre.y;
    // Correction in orientation of pelvis
    _calibrationCorrection.deltaPhiPelvis = (PI / 2.0) - Sequence::getPelvisOrientation(pelvisMarkers);
    // Y-correction for feet
    _calibrationCorrection.deltaYLeftFoot = -leftFootCentre.y;
    _calibrationCorrection.deltaYRightFoot = -rightFootCentre.y;

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
        cerr << "Subject::calibrate(): invalid left foot calibration file!" << endl;
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
        cerr << "Subject::calibrate(): invalid right foot calibration file!" << endl;
    }

    // compute the orientation error for left and right feet
    _calibrationCorrection.deltaPhiLeftFoot = (PI / 2.0) - Sequence::getFootOrientation(leftFootMarkers);
    _calibrationCorrection.deltaPhiRightFoot = (PI / 2.0) - Sequence::getFootOrientation(rightFootMarkers);

    if(DEBUG)
    {
        cout << "Subject::calibrate(): subject #" << _subjectNumber << " calibrated" << endl;
    }
}
