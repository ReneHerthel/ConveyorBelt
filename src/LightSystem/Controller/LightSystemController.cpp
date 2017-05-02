/*
 * LightSystemController_new.cpp
 *
 *  Created on: 24.04.2017
 *      Author: Matthis Keppner
 */

#include "LightSystemController.h"

LightSystemController :: LightSystemController(int chid, BLightSystem* boundary)
	: isRunning(true)
    , chid(chid)
	, boundary(boundary)
	, frequency(ALWAYS_OFF)
	, color(ALL)
{
	 taskThread = thread(&LightSystemController::task, this);
	 controlThread = thread(&LightSystemController::control, this);
}


/**
 * TODO: Start light thread, process pulse messages and set thread control variables
 */

int LightSystemController::task(){
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		std::cout << "Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

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

int LightSystemController::control() {
	struct _pulse pulse;
	int msg;
	while(isRunning)
		msg = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
		if(msg < 0) {
			// TODO error handling
			std::cout << "client MsgReceive_r failed" << std::endl;
		}

		/* FIXME: Typesafe conversion */
		Level warningLevel = (Level) pulse.value.sival_int;

	    static const LightMessage LightMessageMapping[] = {
	            { GREEN, ALWAYS_ON }, // OPERATING
	            { GREEN, ALWAYS_OFF }, // NOT_OPERATING
	            { YELLOW, SLOW_BLINKING }, // WARNING
	            { YELLOW, ALWAYS_OFF }, // CLEAR_WARNING
	            { RED, ALWAYS_OFF }, // CLEAR_ERROR
	            { RED, FAST_BLINKING }, // ERROR_OCCURED
	            { RED, ALWAYS_ON }, // ERROR_ACKNOWLEDGED
	            { RED, SLOW_BLINKING }, // ERROR_GONE_UNACKNOWLEDGED
	            { ALL, ALWAYS_OFF } // CLEAR_ALL
	    };

	    color = LightMessageMapping[warningLevel].color;
	    frequency = LightMessageMapping[warningLevel].frequency;
	/* FXIME: Bogus return value */
	return 1;
}







