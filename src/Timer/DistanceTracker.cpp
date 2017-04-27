/*
 * DistanceTracker.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceTracker.h"
#include "TimerService.h"

DistanceTracker::DistanceTracker(int chid, char code, int value)
	: timer(new TimerService(chid, code, value)) {}

DistanceTracker::~DistanceTracker() {
	delete timer;
}

void DistanceTracker::setAlarm(DistanceAdapter distance) {
	timer.setAlarm(distance.getTime());
}

