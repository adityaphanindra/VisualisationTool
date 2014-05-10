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

#include <vector>
#include <map>

using namespace std;

///
/// \class Sequence
/// \brief Sequence Class
///
class Sequence
{
private:
    uint                _sequenceNumber; 		///< sequence number
    uint                _targetNumber;          ///< actual target number
    vector<Marker::Frame>       _frames;                ///< all markers in the sequence

public:
	///
	/// \brief Constructor
	/// \param sequenceNumber: sequence number
	///
	Sequence(uint sequenceNumber);

	///
	/// \brief get orientation from foot markers
	/// \param markers: marker data
	/// \return orientation wrt x-axis
	///
	static float getFootOrientation(vector<Marker::MarkerData> markers);

	///
	/// \brief get orientation from pelvis markers
	/// \param markers: marker data
	/// \return orientation wrt x-axis
	///
	static float getPelvisOrientation(vector<Marker::MarkerData> markers);

    ///
    /// \brief applySmoothingFilter, applies the smoothing filter on the marker data
    /// \param markers: input markers
    /// \return output markers (smoothed)
    ///
    static vector<Marker::MarkerData> applySmoothingFilter(vector<Marker::MarkerData> markers);

    ///
    /// \brief applyInterpolation, applies the smoothing filter on the marker data
    /// \param markers: input markers
    /// \param type: select the type of interpolation to be applied
    /// \return output markers (interpolated)
    ///
    static vector<Marker::MarkerData> applyInterpolation(vector<Marker::MarkerData> markers, InterpolationType type);

    ///
    /// \brief ignoreFrames: ignore the frames from the sequence
    /// \param from: from frame number
    /// \param to: to frame number
    ///
    void ignoreFrames(uint from, uint to);

private:
};


#endif
