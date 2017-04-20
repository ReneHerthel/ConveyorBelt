/*
 * Distance.h
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_DISTANCEADAPTER_H_
#define SRC_TIMER_DISTANCEADAPTER_H_

typedef unsigned int millimeters;
typedef unsigned int milliseconds;

class DistanceAdapter {
private:
	milliseconds time;
	milliseconds calibrateTime;
	float velocity;
public:
	DistanceAdapter(millimeters distance, milliseconds perTime);
	void setDistance(millimeters distance);
	milliseconds getTime();
};

#endif /* SRC_TIMER_DISTANCEADAPTER_H_ */
