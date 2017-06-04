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
	DistanceTracker(int chid, char code) throw(int);
	~DistanceTracker() throw(int);
	void setAlarm(DistanceAdapter distance, int value) throw(int);
	void stopAlarm() throw(int);
	void resumeAlarm() throw(int);
};

#endif /* SRC_TIMER_DISTANCETRACKER_H_ */
