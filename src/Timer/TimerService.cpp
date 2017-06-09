/*
 * TimerService.cpp
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#include "TimerService.h"

#include "Logger.h"
#include "LogScope.h"

#include <sys/neutrino.h>
#include <time.h>
#include <signal.h>

TimerService::TimerService(int chid, char code) throw(int)
	: timerid()
	, code(code) {
	LOG_SCOPE;

	coid = ConnectAttach_r(0, 0, chid, 0, 0);
	if(coid < 0) {
		LOG_ERROR << "Error in ConnectAttach_r\n";
		throw(-coid);
	}
}

TimerService::~TimerService() throw(int) {
	if(timer_delete(timerid) == -1) { // delete the timer
		LOG_ERROR << "Error in timer_delete\n";
		throw(EXIT_FAILURE);
	}
}

void TimerService::setAlarm(milliseconds time, int value) throw(int) {
	// initialize the sigevent
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, code, value);
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		LOG_ERROR << "Error in timer_create\n";
		throw(EXIT_FAILURE);
	}

	unsigned int milliseconds = time;
	unsigned int seconds = 0;

	if(time >= SECOND) {
		milliseconds = time % SECOND;
		seconds = (time - milliseconds);
	}

	timer.it_value.tv_nsec = milliseconds * MILLISECOND;
	timer.it_value.tv_sec = seconds / SECOND;
	timer.it_interval = { 0, 0 }; // Make it a one shot timer

	if(timer_settime(timerid, 0, &timer, NULL) == -1) {
		LOG_ERROR << "Error in timer_settime\n";
		throw(EXIT_FAILURE);
	}
}

void TimerService::stopAlarm() throw(int) {
	if(timer_gettime(timerid, &timer) == -1) { // get the current time of timer
		LOG_ERROR << "Error in timer_gettime\n";
		throw(EXIT_FAILURE);
	}

	if(timer_delete(timerid) == -1) { // delete the timer
		LOG_ERROR << "Error in timer_delete\n";
		throw(EXIT_FAILURE);
	}
}

void TimerService::resumeAlarm() throw(int) {
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) { // create new timer with last values
		LOG_ERROR << "Error in timer_create\n";
		throw(EXIT_FAILURE);
	}

	if(timer_settime(timerid, 0, &timer, NULL) == -1) { // set new timer to resume
		LOG_ERROR << "Error in timer_settime\n";
		throw(EXIT_FAILURE);
	}
}

