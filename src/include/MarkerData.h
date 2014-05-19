///
/// \file MarkerData.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef MARKER_H
#define MARKER_H

#include "StringFunc.h"

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <limits>

class Point2d
{
public:
    float x;            ///< x coordinate of position
    float y;            ///< y coordinate of position
    float orientation;  ///< orientation wrt positive x-axis in radians

    Point2d() :
        x(0.0),
        y(0.0),
        orientation(0.0)
    {

    }

    Point2d(const Point2d& copy) :
        x(copy.x),
        y(copy.y),
        orientation(copy.orientation)
    {
    }

    Point2d(float xcoordinate, float ycoordinate, float orientationInRadians) :
        x(xcoordinate),
        y(ycoordinate),
        orientation(orientationInRadians)
    {

    }

    std::string toString()
    {
        return std::string("x: " + StringFunc::numToString(x) +
                           " y: " + StringFunc::numToString(y) +
                           " orientation: " + StringFunc::numToString(orientation));
    }
};

class Point3d
{
public:
    float x;            ///< x coordinate of position
    float y;            ///< y coordinate of position
    float z;            ///< z coordinate of position
    float orientationX;  ///< orientation wrt x axis in radians
    float orientationZ;  ///< orientation wrt z axis in radians

    Point3d() :
        x(0.0),
        y(0.0),
        z(0.0),
        orientationX(0.0),
        orientationZ(0.0)
    {

    }
};

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
Position getCentre(std::vector<MarkerData> markers);

typedef std::map<uint, Marker::MarkerData > Frame;

typedef std::vector<Marker::MarkerData> MarkerList;
} // end of namespace Marker

#endif
