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

<<<<<<< HEAD
#define MILLISECOND 100000
=======
#define MILLISECOND 1000000
#define SECOND 1000
>>>>>>> 40196ba03028676478194e37328067d1b9460365

class TimerService : public ITimer {
private:
	timer_t timerid;
	char code;
	int value;
	int coid;
	struct sigevent event;
	struct itimerspec timer;
public:
	TimerService(int chid, char code, int value);
	void setAlarm(milliseconds time);
};

#endif /* SRC_TIMER_TIMERSERVICE_H_ */
