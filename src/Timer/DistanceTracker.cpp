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

	switch(speed){
		case FAST:
			remainingTime = timer_.killAlarm();
			if(remainingTime > 0){
				timer_.setAlarm(remainingTime*mmToTimeFast_, lastValue_);
			}
			break;
		case SLOW:
			remainingTime = timer_.killAlarm();
			if(remainingTime > 0){
				timer_.setAlarm(remainingTime*mmToTimeSlow_, lastValue_);
			}
			break;
		case STOP:
			remainingTime = timer_.killAlarm();
			if(remainingTime > 0){
				timer_.setAlarm(remainingTime*mmToTimeSlow_, lastValue_);
			}
			break;
	}
}

int32_t DistanceTracker::startAlarm(int32_t value, uint32_t distanceMm){
	//TODO Implement
}

int32_t DistanceTracker::stopAlarm(){
	//TODO Implement
}

