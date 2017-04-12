/*
 * IDistanceTracker.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_IDISTANCETRACKER_H_
#define SRC_TIMER_IDISTANCETRACKER_H_

<<<<<<< HEAD
typedef unsigned int centimeters;
typedef unsigned int millimeters;

class IDistanceTracker {
public:
	virtual void setAlarm(centimeters distance);
	virtual void setAlarm(millimeters distance);
=======
#include "DistanceAdapter.h"

class IDistanceTracker {
public:
	virtual void setAlarm(DistanceAdapter distance) = 0;
>>>>>>> 40196ba03028676478194e37328067d1b9460365
};



#endif /* SRC_TIMER_IDISTANCETRACKER_H_ */
