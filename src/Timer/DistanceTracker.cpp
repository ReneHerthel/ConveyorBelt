//Sebastian Brueckner 2274473

#include "DistanceTracker.h"
#include "TimerService.h"
#include "DistanceObservable.h"
#include "DistanceEnum.h"
#include "Calibration.h"
#include "Logger.h"
#include "PuckSignal.h"

DistanceTracker::DistanceTracker(int chid, int8_t code):
	chid_(chid),
	code_(code),
	timer_(chid, code),
	stopped_(false),
	manStopped_(false),
	currSpeed_(DistanceSpeed::STOP){

	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.registerObserver(this); //register to observable

	Calibration& cal = Calibration::getInstance();
	fastToSlowFactor_ = cal.getFastToSlow();
	slowToFastFactor_ = cal.getSlowToFast();
}

DistanceTracker::~DistanceTracker(){
	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.unregisterObserver(this); //register to observable
	timer_.stopAlarm();
}


using namespace DistanceSpeed;

void DistanceTracker::notify(DistanceSpeed::speed_t speed){
	if(!manStopped_){
		uint32_t remainingTime = 0;
		if(stopped_){ //Timer was stopped, resume it
			timer_.resumeAlarm();
			stopped_ = false;
		}
		if(currSpeed_ != speed){
			switch(speed){
				case DistanceSpeed::FAST:
					remainingTime = timer_.killAlarm();
					if(remainingTime > 0){
						timer_.setAlarm((uint32_t)((double)remainingTime*slowToFastFactor_), lastValue_);
					}
					currSpeed_ = speed;
					break;
				case DistanceSpeed::SLOW:
					remainingTime = timer_.killAlarm();
					if(remainingTime > 0){
						timer_.setAlarm((uint32_t)((double)remainingTime*fastToSlowFactor_), lastValue_);
					}
					currSpeed_ = speed;
					break;
				case DistanceSpeed::STOP:
					timer_.stopAlarm();
					stopped_ = true;
					break;
			}
		}
	}
}

int32_t DistanceTracker::startAlarm(int32_t value, DistanceSpeed::lb_distance distance, double delta){
	manStopped_ =  false;
	Calibration& cal = Calibration::getInstance();
	lastValue_ = value;
	timer_.stopAlarm();
	uint32_t ms = cal.getCalibration(distance, currSpeed_)*delta;
	PuckSignal::TimerSignal puckTimerSignal;
	puckTimerSignal.value = value;
	LOG_DEBUG << "[DistanceTracker]Puck with" << (int)puckTimerSignal.TimerInfo.puckID << "started a distance tracker \n";
	if(ms > 0){
		timer_.setAlarm(cal.getCalibration(distance, currSpeed_)*delta, value);
		LOG_DEBUG << "[DistanceTracker]Starting DistanceTracker with " << ms << "ms \n";
	} else {
		timer_.setAlarm(cal.getCalibration(distance, DistanceSpeed::speed_t::FAST)*delta, value); //TODO Quick and dirty fix for creating timer while band is stopped
		notify(DistanceSpeed::speed_t::STOP);
		LOG_DEBUG << "[DistanceTracker]Trying to start Distance tracker with 0, started fast instead and stopped it \n";
	}
}

int32_t DistanceTracker::stopAlarm(){
	LOG_DEBUG << "[DistanceTracker]Stopped distance tracker \n";
	manStopped_ = true;
	timer_.stopAlarm();
}

