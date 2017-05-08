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
	DistanceTracker(int chid, char code);
	~DistanceTracker();
	void setAlarm(DistanceAdapter distance, int value);
	void stopAlarm();
	void resumeAlarm();
};

#endif /* SRC_TIMER_DISTANCETRACKER_H_ */
