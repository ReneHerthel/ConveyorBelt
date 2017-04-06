/*
 * TimerService.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_TIMERSERVICE_H_
#define SRC_TIMER_TIMERSERVICE_H_

#include "ITimer.h"

#include <time.h>
#include <signal.h>

#define MILLI 100000
#define NONE 0

class TimerService : public ITimer {
private:
	timer_t timerid;
	struct sigevent event;
	struct itimerspec timer;
public:
	TimerService(int chid, char code, int value);
	~TimerService();
	void setAlarm(milliseconds time, unsigned int messageData);
};

#endif /* SRC_TIMER_TIMERSERVICE_H_ */
