/*
 * HeightService.h
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#ifndef HEIGHSERVICE_H_
#define HEIGHSERVICE_H_

#include "PulseMessageSenderService.h"

class HeightService {
public:
	/**
	 * @param chid the channel the service should use to communicate with the serial
	 */
	HeightService(int chid);

	void startMeasuring();

	void stopMeasuring();

private:
	PulseMessageSenderService pms;
};

#endif /* HEIGHSERVICE_H_ */
