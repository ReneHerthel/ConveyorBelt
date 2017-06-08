/*
 * DistanceObservable.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#include "DistanceObservable.h"


void DistanceObservable::updateSpeed(DistanceSpeed::speed_t speed){
	for (set<DistanceTracker*>::iterator it = dtlist_.begin(); it != dtlist_.end(); ++it) {
				(*it)->notify(speed);
	}
}

void DistanceObservable::registerObserver(DistanceTracker *dt){
	dtlist_.insert(dt);
}

void DistanceObservable::unregisterObserver(DistanceTracker *dt){
	dtlist_.erase (dt);
}

uint32_t DistanceObservable::getCalibrationData(DistanceSpeed::speed_t speed){
	switch(speed){
		case DistanceSpeed::FAST: return mmToTimeFast_;
		case DistanceSpeed::SLOW: return mmToTimeSlow_;
	}
}

void DistanceObservable::setCalibrationData(DistanceSpeed::speed_t speed, uint32_t mmToTime){
	switch(speed){
		case DistanceSpeed::FAST: mmToTimeFast_ = mmToTime; break;
		case DistanceSpeed::SLOW: mmToTimeSlow_ = mmToTime; break;
	}
}

DistanceObservable& DistanceObservable::getInstance(void){
	static DistanceObservable instance;
	return instance;
}

