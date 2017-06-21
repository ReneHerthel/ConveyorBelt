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
	, color(ALL_COLORS)
    , chid(chid)
	, boundary(boundary)
{
	LOG_SCOPE;
	LOG_DEBUG << "__FUNCTION__: Create threads" << endl;
	taskThread = new thread(&LightSystemController::task, this);
	controlThread = new thread(&LightSystemController::control, this,chid);
}

LightSystemController::~LightSystemController() {
	LOG_SCOPE;
	isRunning = false;

	/*
	 * Release control for shutdown and turn off light.
	 */
	int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, chid, 0, 0);
	if(coid < 0) {
        /* FIXME: Discuss sane error handling for message infrastructure failure */
	   	LOG_ERROR << "Channel Attach failed" << endl;
	}

    /* FIXME: Discuss log message format */
	LOG_DEBUG << "Send message | Channel " << chid << " | ID " << LIGHT_SYSTEM << endl;

    int err = MsgSendPulse_r(coid, sched_get_priority_min(0), LIGHT_SYSTEM, CLEAR_ALL);
    if(err) {
        /* FIXME: Discuss sane error handling for message infrastructure failure */
        LOG_ERROR << "Sending message failed" << endl;
    }
    LOG_DEBUG << "Stopped threads" << endl;
	LOG_DEBUG << "Wait for control to join" << endl;
	controlThread->join();
	LOG_DEBUG << "Wait for task to join" << endl;
	taskThread->join();
    delete controlThread;
    LOG_DEBUG << "Delete control" << endl;
    delete taskThread;
    LOG_DEBUG << "Delete task" << endl;
}

int LightSystemController::task(){
	LOG_SCOPE;
	thread::id thread_id = this_thread::get_id();

    /* FIXME: Move to PortA singleton */
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		LOG_ERROR << thread_id << ": Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

	LOG_DEBUG << thread_id << ": Enter loop" << endl;
	while(isRunning) {
		if (frequency == ALWAYS_OFF)
		{
            /*
             * Switch off all lights in case color changes after
             * entering this condition block
             */
			LOG_DEBUG << thread_id << ": Turn off lights" << endl;
			boundary->lightOff(ALL_COLORS);
		} else if ( ( frequency == ALWAYS_ON ) & boundary->checkIfPreviouslySetTo(color) ) {
			/* Do nothing */
		} else {
			LOG_DEBUG << thread_id << ": Set color to " << color << endl;
			boundary->lightOn(color);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
        /*
         * Blinking is realized by turning off the lights in the second
         * half of the period
         */
		if(frequency == FAST_BLINKING || frequency == SLOW_BLINKING)
		{
            /*
             * Switch off all lights in case color changes after
             * entering this condition block
             */
			boundary->lightOff(ALL_COLORS);
		}
		this_thread::sleep_for(std::chrono::milliseconds(frequency));
		LOG_DEBUG << thread_id << ": isRunning = " << isRunning << " | frequency = " << frequency << " | color = " << color << endl;
	}

	return 0;
}

int LightSystemController::control(int chid) {
	LOG_SCOPE;
    /*! Last received message will be stored here */
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

		/* TODO: Sanitize input, set color and frequency if warningLevel is in range */
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
	            { ALL_COLORS, ALWAYS_OFF } // CLEAR_ALL
	    };

	    color = LightMessageMapping[warningLevel].color;
	    LOG_DEBUG << thread_id << ": Set color " << color << endl;
	    frequency = LightMessageMapping[warningLevel].frequency;
	    LOG_DEBUG << thread_id << ": Set frequency " << frequency << endl;
	}
	/* FIXME: Bogus return value */
	return 0;
}

