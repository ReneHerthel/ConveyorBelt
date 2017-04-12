/*
 * DistanceTracker.h
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_DISTANCETRACKER_H_
#define SRC_TIMER_DISTANCETRACKER_H_

#include "IDistanceTracker.h"
#include "ITimer.h"

class DistanceTracker : public IDistanceTracker {
private:
	ITimer *timer;
public:
	DistanceTracker(int chid, char code, int value);
	~DistanceTracker();
	void setAlarm(DistanceAdapter distance);
};

#endif /* SRC_TIMER_DISTANCETRACKER_H_ */
