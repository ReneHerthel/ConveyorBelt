/*
 * DistanceObservable.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#include "DistanceObservable.h"


void DistanceObservable::updateSpeed(DistanceSpeed::speed_t speed){
	currSpeed_ = speed;
	for (set<DistanceTracker*>::iterator it = dtlist_.begin(); it != dtlist_.end(); ++it) {
				(*it)->notify(speed);
	}
}

void DistanceObservable::registerObserver(DistanceTracker *dt){
	dtlist_.insert(dt);
	dt->notify(currSpeed_); //A new Distance Tracker need to know the current speed, cant wait till next update
}

void DistanceObservable::unregisterObserver(DistanceTracker *dt){
	dtlist_.erase (dt);
}

uint32_t DistanceObservable::getCalibrationData(DistanceSpeed::speed_t speed){
	switch(speed){
		case DistanceSpeed::FAST: return mmToTimeFast_;
		case DistanceSpeed::SLOW: return mmToTimeSlow_;
		case DistanceSpeed::STOP: return 0; //This triggers wrong behavior
	}
	return 0;
}

void DistanceObservable::setCalibrationData(DistanceSpeed::speed_t speed, uint32_t mmToTime){
	switch(speed){
		case DistanceSpeed::FAST: mmToTimeFast_ = mmToTime; break;
		case DistanceSpeed::SLOW: mmToTimeSlow_ = mmToTime; break;
		case DistanceSpeed::STOP: /*Nothing to do*/ break;
	}
}

DistanceObservable& DistanceObservable::getInstance(void){
	static DistanceObservable instance;
	return instance;
}

