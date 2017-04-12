/*
 * Distance.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceAdapter.h"

DistanceAdapter::DistanceAdapter(millimeters distance, milliseconds perTime)
	: time(0)
	, calibrateTime(perTime)
	, velocity(distance/calibrateTime) {}

void DistanceAdapter::setDistance(millimeters distance) {
	time = distance / (velocity * calibrateTime);
}

milliseconds DistanceAdapter::getTime() {
	return time;
}

