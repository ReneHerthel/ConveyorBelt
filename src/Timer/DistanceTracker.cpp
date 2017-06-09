//Sebastian Brueckner 2274473

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


using namespace DistanceSpeed;

void DistanceTracker::notify(DistanceSpeed::speed_t speed){
	uint32_t remainingTime = 0;
	if(currSpeed_ != speed){
		switch(speed){
			case FAST:
				remainingTime = timer_.killAlarm();
				if(remainingTime > 0){
					timer_.setAlarm(remainingTime/mmToTimeSlow_*mmToTimeFast_, lastValue_);
				}
				break;
			case SLOW:
				remainingTime = timer_.killAlarm();
				if(remainingTime > 0){
					timer_.setAlarm(remainingTime/mmToTimeFast_*mmToTimeSlow_, lastValue_);
				}
				break;
			case STOP:
				remainingTime = timer_.killAlarm();
				if(remainingTime > 0){
					timer_.stopAlarm();
				}
				break;
		}
	currSpeed_ = speed;
	}
}

int32_t DistanceTracker::startAlarm(int32_t value, uint32_t distanceMm){
	lastValue_ = value;
	timer_.stopAlarm();
	switch(currSpeed_){
		case FAST:
			timer_.setAlarm(distanceMm*mmToTimeFast_, lastValue_);
			break;
		case SLOW:
			timer_.setAlarm(distanceMm*mmToTimeSlow_, lastValue_);
			break;
		case STOP:
			break;
	}
}

int32_t DistanceTracker::stopAlarm(){
	timer_.stopAlarm();
}

