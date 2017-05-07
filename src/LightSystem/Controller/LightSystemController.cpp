/**
 *       @file  LightSystemController.cpp
 *      @brief  Implement controller
 *
 *     @author: Matthis Keppner <matthis.keppner@haw-hamburg.de>
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  04/24/2017
 *   Copyright  Copyright (c) 2017 Matthis Keppner
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#include "LightSystemController.h"

LightSystemController::LightSystemController(int chid, BLightSystem* boundary)
	: isRunning(true)
	, frequency(ALWAYS_OFF)
	, color(ALL)
    , chid(chid)
	, boundary(boundary)
{
	LOG_SCOPE;
	LOG_DEBUG << "__FUNCTION__: Create threads" << endl;
	taskThread = thread(&LightSystemController::task, this);
	controlThread = thread(&LightSystemController::control, this,chid);
}

int LightSystemController::task(){
	LOG_SCOPE;
	thread::id thread_id = this_thread::get_id();

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

	LOG_DEBUG << thread_id << ": Enter loop" << endl;
	while(isRunning) {
		if (frequency == ALWAYS_OFF)
		{
            /* Switch off all lights in case color changes after
             * entering this condition block */
			boundary->lightOff(ALL);
		} else {
			boundary->lightOn(color);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
        /* Blinking is realized by turning off the lights in the second
         * half of the period */
		if(frequency == FAST_BLINKING || frequency == SLOW_BLINKING)
		{
            /* Switch off all lights in case color changes after
             * entering this condition block */
			boundary->lightOff(ALL);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
	}

	return 1;
}

int LightSystemController::control(int chid) {
	LOG_SCOPE;
    /** Last received message will be stored here */
	struct _pulse pulse;
	int err;
	thread::id thread_id = this_thread::get_id();

	LOG_DEBUG << thread_id << ": Enter loop" << endl;
	LOG_DEBUG << thread_id << ": Channel "<< chid << endl;
	while(isRunning) {
		LOG_DEBUG << thread_id << ": Wait for message on channel " << chid << endl;
		err = MsgReceivePulse_r(chid, &pulse, sizeof(_pulse), NULL);
		LOG_DEBUG << "Message received: " << pulse.value.sival_int << endl;
		if(err < 0) {
			LOG_ERROR << thread_id << ": client MsgReceive_r failed" << std::endl;
		}

		/* FIXME: Typesafe conversion */
		Level warningLevel = (Level) pulse.value.sival_int;

        /* FIXME: Move this up onto class level */
	    static const LightMessage LightMessageMapping[] = {
	            { GREEN, ALWAYS_ON }, // OPERATING
	            { GREEN, ALWAYS_OFF }, // NOT_OPERATING
	            { YELLOW, SLOW_BLINKING }, // WARNING_OCCURED
	            { YELLOW, ALWAYS_OFF }, // CLEAR_WARNING
	            { RED, ALWAYS_OFF }, // CLEAR_ERROR
	            { RED, FAST_BLINKING }, // ERROR_OCCURED
	            { RED, ALWAYS_ON }, // ERROR_ACKNOWLEDGED
	            { RED, SLOW_BLINKING }, // ERROR_GONE_UNACKNOWLEDGED
	            { ALL, ALWAYS_OFF } // CLEAR_ALL
	    };

	    color = LightMessageMapping[warningLevel].color;
	    LOG_DEBUG << thread_id << ": Set color " << color << endl;
	    frequency = LightMessageMapping[warningLevel].frequency;
	    LOG_DEBUG << thread_id << ": Set frequency " << frequency << endl;
	}
	/* FIXME: Bogus return value */
	return 1;
}

