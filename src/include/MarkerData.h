///
/// \file MarkerData.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef MARKER_H
#define MARKER_H

#include <iostream>
#include <mutex>
#include <vector>
#include <map>

using namespace std;

namespace Marker
{
///
/// \struct Position
/// \brief Marker Position 
///
struct Position
{
	float x;
	float y;
	float z;
}; // End of struct Position

///
/// \struct TwoDPoint
/// \brief A 2-d point with x, y and orientation
///
struct TwoDPoint
{
    float x;
    float y;
    float orientation;
    TwoDoPoint() :
        x(Infinity),
        y(Infinity),
        orientation(Infinity)
    {

    }

};

///
/// \class MarkerData
/// \brief data wrt one marker
///
class MarkerData
{
private:
	Position 				_position;	///< position of marker
	std::string				_timestamp;	///< timestamp of recording
	std::mutex 				_mutexLock;	///< lock
public:
	///
	/// \brief Constructor
	///
	MarkerData();
	///
	/// \brief Copy Constructor
	///
	MarkerData(const MarkerData &);
	///
	/// \brief get the marker position
	///	\return Position
	///
	Position getPosition();
	///
	/// \brief set the marker position
	///	\param pos: position of marker
	///
	void setPosition(Position pos);
	///
	/// \brief set the x coordinate
	///	\param x: x position
	///
	void setPositionX(float x);
	///
	/// \brief set the y coordinate
	///	\param y: y position
	///
	void setPositionY(float y);
	///
	/// \brief set the z coordinate
	///	\param z: z position
	///
	void setPositionZ(float z);
	///
	/// \brief checks if marker position is valid
	///	\return true if valid
	///
	bool isValid();
	///
	/// \brief set the timestamp of marker data
	///	\param timestamp: timestamp of recording
	///
	void setTimestamp(std::string timestamp);
	///
	/// \brief get the timestamp of marker data
	///	\return timestamp
	///
	std::string getTimestamp();
	///
	/// \brief get the marker data in the form of string
	///	\return marker data in the form of string
	///
	std::string getString();
}; // End of class MarkerData

///
/// \brief get the centre of markers
/// \param vector of markers
///	\return Position
///
Position getCentre(vector<MarkerData> markers);

typedef map<uint, Marker::MarkerData > Frame;
}; // end of namespace Marker

#endif
