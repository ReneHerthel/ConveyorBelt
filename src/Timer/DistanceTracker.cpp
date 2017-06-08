/*
 * DistanceTracker.cpp
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#include "DistanceTracker.h"
#include "TimerService.h"
#include "DistanceObservable.h"
#include "DistanceEnum.h"

DistanceTracker::DistanceTracker(int chid, int8_t code):
	chid_(chid),
	code_(code),
	timer_(chid, code){

	DistanceObservable& distO = DistanceObservable::getInstance();

	//init conv data
	mmToTimeFast_ = distO.getCalibrationData(DistanceSpeed::FAST);
	mmToTimeSlow_ = distO.getCalibrationData(DistanceSpeed::SLOW);

	distO.registerObserver(this); //register to observable
}

DistanceTracker::~DistanceTracker(){
	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.unregisterObserver(this); //register to observable
}


void DistanceTracker::notify(DistanceSpeed::speed_t speed){
	//TODO Implement
}

int32_t DistanceTracker::startAlarm(int32_t value, uint32_t distanceMm){
	//TODO Implement
}

int32_t DistanceTracker::stopAlarm(){
	//TODO Implement
}

