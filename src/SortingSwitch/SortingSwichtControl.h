/*
 * SortingSwichtControl.h
 *
 *  Created on: 15.06.2017
 *      Author: aca619
 */

#include "DistanceTracker.h"
#include "SortingSwitchService.h"
#include "PulseMessageReceiverService.h"

#ifndef SORTINGSWICHTCONTROL_H_
#define SORTINGSWICHTCONTROL_H_

#define SSC_CLOSE ((int8_t)19) ///Just some number for the code

class SortingSwichtControl {
public:

	void open(void);

	void close(void);

	SortingSwichtControl(int chid);
	virtual ~SortingSwichtControl();

private:
	DistanceTracker distTracker;
	SortingSwitchService ssService;
};

#endif /* SORTINGSWICHTCONTROL_H_ */
