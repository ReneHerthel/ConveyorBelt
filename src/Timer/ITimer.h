/*
 * ITimer.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef TIMER_ITIMER_H_
#define TIMER_ITIMER_H_

class ITimer {
public:
	typedef unsigned int milliseconds;
	virtual void setAlarm(milliseconds time, int value) = 0;
	virtual void stopAlarm() = 0;
	virtual void resumeAlarm() = 0;
	virtual milliseconds killAlarm() = 0;
};

#endif /* TIMER_BTIMER_H_ */
