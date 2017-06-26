/*
 * DistanceObservable.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#include "DistanceObservable.h"
#include "LogScope.h"

void DistanceObservable::updateSpeed(DistanceSpeed::speed_t speed){
	LOG_SCOPE;
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

DistanceObservable& DistanceObservable::getInstance(void){
	static DistanceObservable instance;
	return instance;
}

