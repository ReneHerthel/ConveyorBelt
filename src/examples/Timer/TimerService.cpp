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

TimerService::TimerService(int chid, char code, int value)
	: timerid()
	, code(code)
	, value(value) {
	coid = ConnectAttach_r(0, 0, chid, 0, 0);
	if(coid < 0) {
		// TODO error handling
	}
}

void TimerService::setAlarm(milliseconds time) {
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, code, value);
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		// TODO error handling
	}

	timer.it_value.tv_nsec = time * MILLISECOND;
	timer.it_value.tv_sec = 0;
	timer.it_interval = { 0, 0 }; // Make it a one shot timer
	timer_settime(timerid, 0, &timer, NULL);
}

