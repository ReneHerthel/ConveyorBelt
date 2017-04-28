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

HeightMeasurementService::HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr)
    :    stateMachine(send_chid)
    ,    calibrationDataPtr(calibrationDataPtr)
{
    // Creates the thread for the measurement with the receive channel to send on it.
    measurementThread = std::thread(&HeightMeasurementService::measuringTask, this, receive_chid);
    // Creates the thread for the statemachine with the receive channel to listen on it.
    stateMachineThread = std::thread(&HeightMeasurementService::stateMachineTask, this, receive_chid);
}

HeightMeasurementService::~HeightMeasurementService() {
    // Nothing todo so far.
}

void HeightMeasurementService::measuringTask(int receive_chid) {
    int16_t data = 0;                                    /*< The current measured data. */
    HeightContext::Signal state = HeightContext::START;  /*< The current state of the statemachine. */
    int16_t maxHeight = 0;                               /*< The maximum valid height. */
    int16_t minHeight = 0;                               /*< The minimum valid height. */
    HeightMeasurementHal hal;                            /*< The hal object to access the HW. */

    // Connect to the receive channel for sending pulse-messages on it.
    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);

    // Do error handling, if there is no channel available.
    if (coid < 0) {
      // TODO: Error handling.
    }

    /* TODO: Make this thread terminating from outside.
     *       -> volatile bool isRunning.
     * TODO: Make this more fancy.
     *
     * Check if the current measured data is in a valid range of the
     * corresponding calibrated data. If it is so, send a signal to the receive-
     * channel, where the statemachine is listening and could do the next
     * transition.
     */
    while (1) {
        hal.read(data);

        maxHeight = data + DELTA_VAL;
        minHeight = data - DELTA_VAL;

        if (state != HeightContext::REF_HEIGHT) {
            if (maxHeight < REF_HEIGHT_VAL && minHeight > REF_HEIGHT_VAL) {
                // TODO
            }
        }
        else if (state != HeightContext::HOLE_HEIGHT) {
            if (maxHeight < HOLE_HEIGHT_VAL && minHeight > HOLE_HEIGHT_VAL) {
                // TODO
            }
        }
        else if (state != HeightContext::SURFACE_HEIGHT) {
            if (maxHeight < SURFACE_HEIGHT_VAL && minHeight > SURFACE_HEIGHT_VAL) {
                // TODO
            }
        }
        else if (state != HeightContext::LOW_HEIGHT) {
            if (maxHeight < LOW_HEIGHT_VAL && minHeight > LOW_HEIGHT_VAL) {
                // TODO
            }
        }
        else if (state != HeightContext::HIGH_HEIGHT) {
            if (maxHeight < HIGH_HEIGHT_VAL && minHeight > HIGH_HEIGHT_VAL) {
                // TODO
            }
        }
    }
}

void HeightMeasurementService::stateMachineTask(int receive_chid) {
    // Connect the statemachine to the receive channel to listen on it.
    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);

    // Do error handling if there is no channel to connect.
    if (coid < 0) {
        // TODO: Error handling.
    }

    // Structure that describes a pulse.
    struct _pulse pulse;

    /* TODO: Make this thread terminating from outside.
     *       -> volatile bool isRunning.
     *
     * Wait for a new incoming pulse-message to do the next transition.
     */
    while (1) {

        // Returns 0 on success and a negative value on error.
        int err = MsgReceivePulse_r(receive_chid, &pulse, sizeof(_pulse), NULL);

        // Do error handling, if there occurs an error.
        if (err < 0) {
            // TODO: Error handling.
            // EFAULT, EINTR, ESRCH, ETIMEDOUT -> see qnx-manual.
        }

        // Signalize the statemachine for the next transition.
        stateMachine.process((HeightContext::Signal) pulse.value.sival_int);
    }
}

/** @} */
