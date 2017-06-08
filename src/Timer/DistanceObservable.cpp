/*
 * DistanceObservable.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#include "DistanceObservable.h"


void DistanceObservable::updateSpeed(speed_t speed){
	for (vector<DistanceTracker*>::iterator it = dtlist_.begin(); it != dtlist_.end(); ++it) {
				(*it)->notify(speed);
	}
}

void DistanceObservable::registerObserver(DistanceTracker *dt){
	dtlist_.insert(dt);
}

void DistanceObservable::registerObserver(DistanceTracker *dt){
	dtlist_.erase (dt);
}

uint32_t DistanceObservable::getCalibrationData(speed_t speed){
	switch(speed){
		case FAST: return mmToTimeFast_;
		case SLOW: return mmToTimeSlow_;
	}
}

void DistanceObservable::setCalibrationData(speed_t speed, uint32_t mmToTime){
	switch(speed){
		case FAST: mmToTimeFast_ = mmToTime; break;
		case SLOW: mmToTimeSlow_ = mmToTime; break;
	}
}

static DistanceObservable& DistanceObservable::getInstance(void){
	static DistanceObservable instance;
	return instance;
}

