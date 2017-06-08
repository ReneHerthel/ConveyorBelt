/*
 * DistanceTracker.h
 *
 *  Created on: 12.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_TIMER_DISTANCETRACKER_H_
#define SRC_TIMER_DISTANCETRACKER_H_

#include "ITimer.h"

class DistanceTracker{
private:
	ITimer *timer;
public:
	/**
	 *Send a Signal when the conveyor belt has covered a certain distance
	 *@param chid The Channel the DistanceTracker will send a signal, when distance was covered
	 *@param code The code of the Pulse that will be send
	 */
	DistanceTracker(int chid, int8_t code);

	/**
	 * Cleanup the timers used by the logger
	 */
	~DistanceTracker();

	/**
	 * Notify this DistanceTracker over the change of speed
	 * The Distance tracker will adapt his timers accordingly
	 * @param speed The current speed of the belt
	 */
	void notify(speed_t speed);

	/**
	 *Start an Alarm, will override any alarm pending
	 *@param value The Signal Value that will be passed when the distance was covered
	 *@param distanceMm The distance in millimetres
	 *@return -1 when setting the alarm failed
	 */
	int32_t startAlarm(int32_t value, uint32_t distanceMm);

	/**
	 *Stop the Alarm from this distance tracker
	 *@return -1 if the disabling of the alarm failed
	 */
	int32_t stopAlarm();

};

#endif /* SRC_TIMER_DISTANCETRACKER_H_ */
