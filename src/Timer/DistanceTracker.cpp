/*
 * DistanceTracker.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceTracker.h"
#include "TimerService.h"

DistanceTracker::DistanceTracker(int chid, char code) throw(int)
	: timer(new TimerService(chid, code)) {}

DistanceTracker::~DistanceTracker() throw(int) {
	delete timer;
}

void DistanceTracker::setAlarm(DistanceAdapter distance, int value) throw(int) {
	timer->setAlarm(distance.getTime(), value);
}

void DistanceTracker::stopAlarm() throw(int) {
	timer->stopAlarm();
}

void DistanceTracker::resumeAlarm() throw(int) {
	timer->resumeAlarm();
}

