/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Service function declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#include "HeightMeasurementService.h"
#include "HeightMeasurementHal.h"
#include "Logger.h"
#include "LogScope.h"

#include <chrono>
#include <algorithm>
#include <climits>

/*
 * @brief Macros to check if the measured data is in range of the corresponding state.
 *
 * @param [DATA] The measured data.
 * @param [CAL]  The reference value of the calibrated data.
 */
#define RANGE(DATA, CAL)    (((DATA - DELTA_VAL) < CAL) && ((DATA + DELTA_VAL) > CAL))

using namespace HeightMeasurement;

HeightMeasurementService::HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr)
    :    calibrationDataPtr(calibrationDataPtr)
    ,    receive_chid(receive_chid)
	, 	 measurementIsRunning(false)
{
    LOG_SCOPE;
    // Set this to true, so the statemachine thread will run his superloop.
    statemachineIsRunning = true;
    // Creates the thread for the statemachine with the receive channel to listen on it.
    stateMachineThread = std::thread(&HeightMeasurementService::stateMachineTask, this, receive_chid);

    highestHeight = USHRT_MAX;	// maximum value

    stateMachine = new HeightContext(send_chid, this);
    LOG_DEBUG << "[HeightMeasurementService] Constructor  measurementIsRunning \n" << measurementIsRunning << "\n";
}

HeightMeasurementService::~HeightMeasurementService() {
	statemachineIsRunning = false;
	stateMachineThread.join();
    delete stateMachine;
}

void HeightMeasurementService::startMeasuring() {
	if(!measurementIsRunning) { // FIXME: This should not be tested. This is required by the state machine
		LOG_DEBUG << "[HeightMeasurementService] startMeasuring() \n";
		// Set this true, so the measurement thread will run his superloop.
		measurementIsRunning = true;
		// Creates the thread for the measurement with the receive channel to send on it.
    	measurementThread = std::thread(&HeightMeasurementService::measuringTask, this, receive_chid);
	}
}

void HeightMeasurementService::stopMeasuring() {
	LOG_DEBUG << "[HeightMeasurementService] measurementIsRunning: " << measurementIsRunning << "\n";
	if(measurementIsRunning){
	    measurementIsRunning = false;
	    measurementThread.join();
	}
}

void HeightMeasurementService::measuringTask(int receive_chid) {
    LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightMeasurementService] measuringTask() Thread started\n";

    uint16_t data = 0;             	/*< The current measured data.*/
    Signal state = START;         	/*< The current state of the statemachine.*/
    Signal oldState = state;      	/*< The old state of the statemachine.*/
    HeightMeasurementHal hal;     	/*< The hal object to access the HW.*/
    int err = 0;                  		/*< Return value of msgSend.*/

    // Connect to the receive channel for sending pulse-messages on it.
    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);

    // Do error handling, if there is no channel available.
    if (coid < 0) {
        // TODO: Error handling.
        LOG_DEBUG << "[HeightMeasurementService] measuringTask() ConnectAttach_r failed\n";
    }

    /* Check if the current measured data is in a valid range of the
     * corresponding calibrated data. If it is so, send a signal to the receive-
     * channel, where the statemachine is listening and will do the next
     * transition.
     */
    uint16_t dataWindow[WINDOW_SIZE] = {0};
    uint32_t writePos = 0;
    while (measurementIsRunning) {
    	  hal.read(data);
    	  dataInRange(&state, data);

        if (data < highestHeight) {	// get the highest height (lowest value)
            highestHeight = data;
        }

        dataWindow[writePos++] = data;
        writePos %= WINDOW_SIZE;

        bool valid = true;

        // Filter
        for (int i = 0; i < WINDOW_SIZE - 1; i++) {
        	Signal temp1;
        	Signal temp2;
        	dataInRange(&temp1, dataWindow[i]);
        	dataInRange(&temp2, dataWindow[i + 1]);
        	if(temp1 != temp2) valid = false;
        }

        if(valid) {
			// But send only a message if there is a new state.
			if (state != oldState) {
				err = MsgSendPulse_r(coid, sched_get_priority_min(0), 0, state);
				if (err < 0) {
					// TODO Error handling.
					LOG_DEBUG << "[HeightMeasurementService] measuringTask() MsgSendPulse_r failed.\n";
				}
				LOG_DEBUG << "[HeightMeasurementService] send measuring signal: " << state << "\n";
			}
			// Remember the current state as old state for the next loop.
			oldState = state;
        }
    }
    LOG_DEBUG << "[HeightMeasurementService] measuringTask() Leaves superloop\n";
}

void HeightMeasurementService::dataInRange(Signal *state, uint16_t data) {
    if (RANGE(data, REF_HEIGHT_VAL)) {
        *state = REF_HEIGHT;
    }
    else if (RANGE(data, HOLE_HEIGHT_VAL)) {
    	*state = HOLE_HEIGHT;
    }
    else if (RANGE(data, SURFACE_HEIGHT_VAL)) {
    	*state = SURFACE_HEIGHT;
    }
    else if (RANGE(data, LOW_HEIGHT_VAL)) {
    	*state = LOW_HEIGHT;
    }
    else if (RANGE(data, HIGH_HEIGHT_VAL)) {
    	*state = HIGH_HEIGHT;
    }
    else if (RANGE(data, INVALID_HEIGHT_VAL)){
        *state = INVALID;
    }
}

void HeightMeasurementService::stateMachineTask(int receive_chid) {
    LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Thread started\n";

    struct _pulse pulse; /*< Structure that describes a pulse.*/

    // Wait for a new incoming pulse-message to do the next transition.
    while (statemachineIsRunning) {
        // Returns 0 on success and a negative value on error.
        int err = MsgReceivePulse_r(receive_chid, &pulse, sizeof(_pulse), NULL);

        // Do error handling, if there occurs an error.
        if (err < 0) {
            // TODO: Error handling.
            // EFAULT, EINTR, ESRCH, ETIMEDOUT -> see qnx-manual.
            LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Error on MsgReceivePulse_r\n";
        }

        //LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Received pulse: " << pulse.value.sival_int << "\n";

        // Signalize the statemachine for the next transition.
        stateMachine->process((Signal) pulse.value.sival_int);
    }

    LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Leaves superloop\n";
}

uint16_t HeightMeasurementService::getHighestHeight() {
    return highestHeight;
}

/** @} */
