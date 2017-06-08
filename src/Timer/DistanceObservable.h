/*
 * DistanceObservable.h
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#ifndef DISTANCEOBSERVABLE_H_
#define DISTANCEOBSERVABLE_H_

#include <set>

using namespace std;

class DistanceObservable {
public:
	enum speed_t{
		FAST,
		SLOW,
		STOP
	};

	/**
	 * Update the Speed of all Observers
	 * @param speed the new Speed of the belt
	 */
	void updateSpeed(speed_t speed);

	/**
	 * Register a new DistanceTracker as Observer to this
	 * DistanceObservable
	 * @param dt The pointer to the distance tracker that wants to observ
	 */
	void registerObserver(DistanceTracker *dt);

	/**
	 * Unregister the DistanceTracker
	 */
	void unregisterObserver(DistanceTracker *dt);

	/**
	 * Used by Distance tracker to aquire the mm to time calibration data
	 * stored here centrally
	 * NOTE! Stop doesnt work as speed
	 * @param speed the calibration data for the speed_t
	 */
	uint32_t getCalibrationData(speed_t speed);


	/**
	 * Set the mm to time calibration
	 * NOTE! Stop doesnt work as speed
	 * @param mmToTime the factor used to determin the time
	 * @param speed the calibration data for the speed_t
	 */
	void setCalibrationData(speed_t speed, uint32_t mmToTime);

	/**
	 * Get an Instance of the DistanceObservable
	 */
	static DistanceObservable& getInstance(void);
private:
	//Unused, singelton
	DistanceObservable(){};
	virtual ~DistanceObservable(){};

	set<DistanceTracker*> dtlist_; 	///This list contains all DistanceTracker that are currently registered to the Observable
	uint32_t mmToTimeFast_; 			///Multiply with this to conv the mm to time
	uint32_t mmToTimeSlow_; 			///Multiply with this to conv the mm to time
};

#endif /* DISTANCEOBSERVABLE_H_ */
