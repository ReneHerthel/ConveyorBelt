/*
 * DistanceObservable.h
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#ifndef DISTANCEOBSERVABLE_H_
#define DISTANCEOBSERVABLE_H_

#include <set>
#include <stdint.h>
#include "DistanceTracker.h"
#include "DistanceEnum.h"


using namespace std;

class DistanceTracker;

class DistanceObservable{
public:
	/**
	 * Update the Speed of all Observers
	 * @param speed the new Speed of the belt
	 */
	void updateSpeed(DistanceSpeed::speed_t speed);

	/**
	 * Register a new DistanceTracker as Observer to this DistanceObservable
	 * The Distance tracker will be instantly notified to get the current belt speed
	 * @param dt The pointer to the distance tracker that wants to observ
	 */
	void registerObserver(DistanceTracker *dt);

	/**
	 * Unregister the DistanceTracker
	 */
	void unregisterObserver(DistanceTracker *dt);

	/**
	 * Get an Instance of the DistanceObservable
	 */
	static DistanceObservable& getInstance(void);
private:
	//Unused, singelton
	DistanceObservable(){};
	virtual ~DistanceObservable(){};

	set<DistanceTracker*> dtlist_; 	    ///This list contains all DistanceTracker that are currently registered to the Observable
	DistanceSpeed::speed_t currSpeed_;  ///Current speed of the belt
};

#endif /* DISTANCEOBSERVABLE_H_ */
