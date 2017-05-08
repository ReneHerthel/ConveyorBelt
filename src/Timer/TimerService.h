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
	struct sigevent event;
	struct itimerspec timer;
public:
	TimerService(int chid, char code);
	~TimerService();
	void setAlarm(milliseconds time, int value);
	void stopAlarm();
	void resumeAlarm();
};

#endif /* SRC_TIMER_TIMERSERVICE_H_ */
