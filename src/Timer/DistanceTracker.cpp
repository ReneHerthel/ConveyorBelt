/*
 * DistanceTracker.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceTracker.h"
#include "TimerService.h"

DistanceTracker::DistanceTracker(int chid, char code)
	: timer(new TimerService(chid, code, value)) {}

DistanceTracker::~DistanceTracker() {
	delete timer;
}

void DistanceTracker::setAlarm(DistanceAdapter distance, int value) {
	timer->setAlarm(distance.getTime(), value);
}

void DistanceTracker::stopAlarm() {
	timer->stopAlarm();
}

void DistanceTracker::resumeAlarm() {
	timer->resumeAlarm();
}

