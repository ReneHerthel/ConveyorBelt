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
//#include "ITimer.h"
//#include "TimerService.h"
#include "Logger.h"
#include "LogScope.h"

// TODO delete
#include <iostream>

/*
 * @brief Macros to check if the measured data is in range of the corresponding state.
 *
 * @param [DATA] The measured data.
 * @param [CAL]  The reference value of the calibrated data.
 * @{
 */
#define DATA_IS_IN_RANGE(DATA, CAL)    (((DATA - DELTA_VAL) < CAL) && ((DATA + DELTA_VAL) > CAL))
/** @} */

HeightMeasurementService::HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr)
    :    stateMachine(new HeightContext(send_chid, this))
    ,    calibrationDataPtr(calibrationDataPtr)
	,	 receive_chid(receive_chid)
{
	statemachineIsRunning = true;
    // Creates the thread for the statemachine with the receive channel to listen on it.
    stateMachineThread = std::thread(&HeightMeasurementService::stateMachineTask, this, receive_chid);
}

HeightMeasurementService::~HeightMeasurementService() {
    // TODO Kill the threads.
}

void HeightMeasurementService::startMeasuring() {
	measurementIsRunning = true;
    // Creates the thread for the measurement with the receive channel to send on it.
    measurementThread = std::thread(&HeightMeasurementService::measuringTask, this, receive_chid);
}

void HeightMeasurementService::stopMeasuring() {
	measurementIsRunning = false;
}

void HeightMeasurementService::measuringTask(int receive_chid) {
    LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightMeasurementService] measuringTask() Thread started\n";

    int16_t data = 0;                                    /*< The current measured data.*/
    HeightContext::Signal state = HeightContext::START;  /*< The current state of the statemachine.*/
    HeightContext::Signal oldState = state;              /*< The old state of the statemachine.*/
    HeightMeasurementHal hal;                            /*< The hal object to access the HW.*/
    int err = 0;                                         /*< Return value of msgSend.*/
    //TimerService timerService;                         /*< A timer for timeouts */

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
    while (measurementIsRunning) {
        hal.read(data);

        if (DATA_IS_IN_RANGE(data, REF_HEIGHT_VAL)) {
            state = HeightContext::REF_HEIGHT;
        }
        else if (DATA_IS_IN_RANGE(data, HOLE_HEIGHT_VAL)) {
            state = HeightContext::HOLE_HEIGHT;
        }
        else if (DATA_IS_IN_RANGE(data, SURFACE_HEIGHT_VAL)) {
            state = HeightContext::SURFACE_HEIGHT;
        }
        else if (DATA_IS_IN_RANGE(data, LOW_HEIGHT_VAL)) {
            state = HeightContext::LOW_HEIGHT;
        }
        else if (DATA_IS_IN_RANGE(data, HIGH_HEIGHT_VAL)) {
            state = HeightContext::HIGH_HEIGHT;
        }/* else {
        	state = HeightContext::INVALID;
        }*/

        // TODO: Check for timeouts.

        // Only send a message, when there was a new state.
        if (state != oldState) {
            err = MsgSendPulse_r(coid, sched_get_priority_min(0), 0, state);

            if (err < 0) {
                // TODO Error handling.
                LOG_DEBUG << "[HeightMeasurementService] measuringTask() MsgSendPulse_r failed.\n";
            }
        }

        // Remember the current state as old state for the next loop.
        oldState = state;
    }

    LOG_DEBUG << "[HeightMeasurementService] measuringTask() Leaves superloop\n";
    // TODO: delete timerService;
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

        LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Received pulse: " << pulse.value.sival_int << "\n";

        // Signalize the statemachine for the next transition.
        stateMachine->process((HeightContext::Signal) pulse.value.sival_int);
    }

    LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Leaves superloop\n";
}

/** @} */
