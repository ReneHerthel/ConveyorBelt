/*
 * ITimer.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef TIMER_ITIMER_H_
#define TIMER_ITIMER_H_

typedef unsigned int milliseconds;

class ITimer {
public:

	virtual void setAlarm(milliseconds time) = 0;

};



#endif /* TIMER_BTIMER_H_ */
