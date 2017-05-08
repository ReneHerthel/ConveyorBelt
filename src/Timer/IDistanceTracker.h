/*
 * IDistanceTracker.h
 *
 *  Created on: 05.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_IDISTANCETRACKER_H_
#define SRC_TIMER_IDISTANCETRACKER_H_

#include "DistanceAdapter.h"
typedef unsigned int centimeters;
typedef unsigned int millimeters;

class IDistanceTracker {
public:
	virtual void setAlarm(centimeters distance);
	virtual void setAlarm(millimeters distance);



};



#endif /* SRC_TIMER_IDISTANCETRACKER_H_ */