/*
 * IDistanceTracker.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_IDISTANCETRACKER_H_
#define SRC_TIMER_IDISTANCETRACKER_H_

#include "DistanceAdapter.h"

class IDistanceTracker {
public:
	virtual void setAlarm(DistanceAdapter distance) = 0;
	virtual void stopAlarm() = 0;
	virtual void resumeAlarm() = 0;
};



#endif /* SRC_TIMER_IDISTANCETRACKER_H_ */
