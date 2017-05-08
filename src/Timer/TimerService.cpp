/*
 * TimerService.cpp
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#include "TimerService.h"

#include <sys/neutrino.h>
#include <time.h>
#include <signal.h>

TimerService::TimerService(int chid, char code)
	: timerid()
	, code(code) {
	coid = ConnectAttach_r(0, 0, chid, 0, 0);
	if(coid < 0) {
		// TODO error handling
	}
}

TimerService::~TimerService() {
	if(timer_delete(timerid) == -1) { // delete the timer
		// TODO error handling
	}
}

void TimerService::setAlarm(milliseconds time, int value) {
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, code, value);
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		// TODO error handling
	}

	unsigned int milliseconds = time;
	unsigned int seconds = 0;

	if(time >= SECOND) {
		milliseconds = time % SECOND;
		seconds = (time - milliseconds);
	}

	timer.it_value.tv_nsec = time * MILLISECOND;
	timer.it_value.tv_sec = seconds / SECOND;
	timer.it_interval = { 0, 0 }; // Make it a one shot timer

	if(timer_settime(timerid, 0, &timer, NULL) == -1) {
		// TODO error handling
	}
}

void TimerService::stopAlarm() {
	if(timer_gettime(timerid, &timer) == -1) { // get the current time of timer
		// TODO error handling
	}

	if(timer_delete(timerid) == -1) { // delete the timer
		// TODO error handling
	}
}

void TimerService::resumeAlarm() {
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, code, value);
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		// TODO error handling
	}

	if(timer_settime(timerid, 0, &timer, NULL) == -1) {
		// TODO error handling
	}
}

