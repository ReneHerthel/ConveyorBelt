/*
 * TimerService.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_TIMERSERVICE_H_
#define SRC_TIMER_TIMERSERVICE_H_

#include "ITimer.h"

#include <thread>

#define MILLISECOND 1000000
#define SECOND 1000

class TimerService : public ITimer {
private:
	timer_t timerid;
	char code;
	int coid;
	bool timerRunning;
	bool timerCreated;
	bool timerWasRunning;
	struct sigevent event;
	struct itimerspec timer;
public:
	TimerService(int chid, char code) throw(int);
	~TimerService() throw(int);
	void setAlarm(milliseconds time, int value) throw(int);
	void stopAlarm() throw(int);
	void resumeAlarm() throw(int);
	milliseconds killAlarm() throw(int);
};

#endif /* SRC_TIMER_TIMERSERVICE_H_ */
