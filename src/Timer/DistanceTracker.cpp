/*
 * DistanceTracker.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceTracker.h"

DistanceTracker::DistanceTracker(int chid, char code, int value)
	: timer(chid, code, value) {}

void DistanceTracker::setAlarm(DistanceAdapter distance) {
	timer.setAlarm(distance.getTime());
}

