/*
 * LightSystemController_new.cpp
 *
 *  Created on: 24.04.2017
 *      Author: Matthis Keppner
 */

#include "LightSystemController.h"

LightSystemController :: LightSystemController(int chid, BLightSystem* boundary)
	: isRunning(true)
	, frequency(ALWAYS_OFF)
	, color(ALL)
    , chid(chid)
	, boundary(boundary)
{
	 taskThread = thread(&LightSystemController::task, this);
	 controlThread = thread(&LightSystemController::control, this,chid);
}


/**
 * TODO: Start light thread, process pulse messages and set thread control variables
 */

int LightSystemController::task(){
	LOG_SCOPE;
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

	LOG_DEBUG << "__LINE__: Enter loop" << endl;
	while(isRunning) {
		if (frequency == ALWAYS_OFF)
		{
			boundary->lightOff(color);
		} else {
			boundary->lightOn(color);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
		if(frequency == FAST_BLINKING || frequency == SLOW_BLINKING)
		{
			boundary->lightOff(color);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
	}

	return 1;
}

int LightSystemController::control(int chid) {
	struct _pulse pulse;
	int err;

	LOG_DEBUG << "__LINE__: Enter loop" << endl;
	LOG_DEBUG << "__FUNCTION__: Channel "<< chid << endl;
	while(isRunning) {
	}
	return 1;
}







