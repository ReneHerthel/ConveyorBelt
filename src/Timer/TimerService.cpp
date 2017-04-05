/*
 * TimerService.cpp
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#include "TimerService.h"

#include <sys/neutrino.h>

TimerService::TimerService(int chid, char code, int value)
	: timerid() {
	int coid = ConnectAttach (0, 0, chid, 0, 0);
	if(coid == -1) {
		// TODO error handling
	}

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, code, value);
	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		// TODO error handling
	}
}

TimerService::~TimerService() {

}

void TimerService::setAlarm(milliseconds time, unsigned int messageData) {
	timer.it_value.tv_sec = NONE;
	timer.it_value.tv_nsec = time * MILLI;
	timer_settime(timerid, 0, &timer, NULL);
}

