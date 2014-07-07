///
/// \file Tools.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Tools.h"
#include "Settings.h"

float Tools::wrapToPi(float input) {
	float sign = 1.0;
	if(input < 0)
		sign = -1.0;
	input = sign * fmod(input, 2 * PI);
	if(input > PI)
		return input - 2 * PI;
	else if(input <= -PI)
		return 2 * PI + input;
	else
		return input;
}

float Tools::wrapTo180(float input) {
	float sign = 1.0;
	if(input < 0)
		sign = -1.0;
	input = sign * fmod(input, 360);
	if(input > 180)
		return input - 360;
	else if(input <= -180)
		return 360 + input;
	else
		return input;
}

float Tools::degToRad(float input) {
	return wrapToPi(input * PI / 180.0);
}

float Tools::radToDeg(float input) {
	return wrapTo180(input * 180.0 / PI);
}


Point2d Tools::rotatePoint(Point2d point, float angle) {
    Point2d rotatedPoint;
    rotatedPoint.x = point.x * cos(angle) - point.y * sin(angle);
    rotatedPoint.y = point.x * sin(angle) + point.y * cos(angle);
    rotatedPoint.orientation = Tools::wrapToPi(rotatedPoint.orientation + angle);
    return rotatedPoint;
}

Point2d Tools::translatePoint(Point2d point, float x, float y) {
    return Point2d(point.x + x, point.y + y, point.orientation);
}
