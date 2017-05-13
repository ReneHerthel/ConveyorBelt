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

/*
 * @brief Macros to check if the measured data is in range of the corresponding state.
 *
 * @param [DATA] The measured data.
 * @param [CAL]  The reference value of the calibrated data.
 */
#define RANGE(DATA, CAL)    (((DATA - DELTA_VAL) < CAL) && ((DATA + DELTA_VAL) > CAL))

/*
 * @brief
 */
#define AMOUNT_OF_SIGNALS (6)

/*
 * @brief
 */
#define SAMPLES_AMOUNT (30)

/*
 * @brief
 */
#define SAMPLES_WINDOW_SIZE (3)
#define SAMPLES_WINDOW_END  (SAMPLES_WINDOW_SIZE - 1)
#define SAMPLES_WINDOW_MID  (SAMPLES_WINDOW_SIZE / 2) // 1 in array on size of 3

/*
 * @brief Returns the maximum of two arguments.
 */
#define MAX(x, y)            ((x > y) ? (x) : (y))

/*
 * @brief Returns the minimum of two arguments.
 */
#define MIN(x, y)            ((x < y) ? (x) : (y))

/*
 * @brief
 */
#define MEDIAN_OF_THREE(x, y, z)     ( MAX( MIN( MAX( x, y), z), MIN(x, y)) )

HeightMeasurementService::HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr)
    :    stateMachine(new HeightContext(send_chid, this))
    ,    calibrationDataPtr(calibrationDataPtr)
    ,    receive_chid(receive_chid)
{
    // Set this to true, so the statemachine thread will run his superloop.
    statemachineIsRunning = true;
    // Creates the thread for the statemachine with the receive channel to listen on it.
    stateMachineThread = std::thread(&HeightMeasurementService::stateMachineTask, this, receive_chid);
}

HeightMeasurementService::~HeightMeasurementService() {
    delete stateMachine;
}

void HeightMeasurementService::startMeasuring() {
    // Set this true, so the measurement thread will run his suoperloop.
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

    int16_t data = 0;             /*< The current measured data.*/
    Signal state = START;         /*< The current state of the statemachine.*/
    Signal oldState = state;      /*< The old state of the statemachine.*/
    HeightMeasurementHal hal;     /*< The hal object to access the HW.*/
    int err = 0;                  /*< Return value of msgSend.*/

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
    int counters[AMOUNT_OF_SIGNALS] = {0};
    int window[SAMPLES_WINDOW_SIZE]
    while (measurementIsRunning) {

        for (int i = 0; i < AMOUNT_OF_SAMPLES; i++) {

            hal.read(data);

            // Shift the data to the left by one.
            memmove(window, window + 1, sizeof(window) - sizeof(*window));

            /* Put the new data at the end of the window.
             *
             *        +----+----+----+ ... +----+
             * OUT << | 0  | 1  |  2 | ... | N  | << IN
             *        +----+----+----+ ... +----+
             */
            window[SAMPLES_WINDOW_END] = data;

            /* Calculate the median of three from the window.
             * example:
             * MAX( MIN ( MAX (3, 5), 4), MIN(3, 5))
             * MAX( MIN (5 , 4), 3)
             * MAX( 4, 3)
             * 4 <- median
             */
            int median = MEDIAN_OF_THREE(window[0], window[1], window[2]);

            dataInRange(&state, median);

            counters[state]++;
        }

        // TODO: get highest state?

        /*
        int inRow = 0;
        int heighestCount = 0;
        int heighestCountIndex = 0;
        Signal newSample = state;
        Signal oldSample = START;

        for (int i = 0; i < 64; i++) {
            hal.read(data);
            dataInRange(&newSample, data);

            if (oldSample != START && newSample == oldSample) {
                inRow++;

                if (inRow >= 8) {
                    counters[newSample]++;

                    if (counters[newSample] > heighestCount) {
                    	heighestCount = counters[newSample];
                    	heighestCountIndex = newSample;
                    }

                    inRow = 0;
                }
            }
            else {
            	inRow = 0;
            }

            oldSample = newSample;
        }

        state = Signal(heighestCountIndex);
        */


    	/*
    	int currentCount = 0;
    	Signal tmpState = state;

    	for (int i = 0; i < AMOUNT_OF_SAMPLES; i++) {
          hal.read(data);
          dataInRange(&tmpState, data);
          if(tmpState != oldState) {
                if (++counters[tmpState] > currentCount) {
                    currentCount = counters[tmpState];
                    state = tmpState;
                }
          }

          //std::this_thread::sleep_for(std::chrono::microseconds(50));
    	}
    	*/

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

        // Reset the counters
        std::fill(counters, counters + AMOUNT_OF_SIGNALS, 0);
        std::fill(samples, samples + SAMPLES_AMOUNT, 0);
    }

    LOG_DEBUG << "[HeightMeasurementService] measuringTask() Leaves superloop\n";
}

void HeightMeasurementService::dataInRange(Signal *state, int16_t data) {
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

        LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Received pulse: " << pulse.value.sival_int << "\n";

        // Signalize the statemachine for the next transition.
        stateMachine->process((Signal) pulse.value.sival_int);
    }

    LOG_DEBUG << "[HeightMeasurementService] stateMachineTask() Leaves superloop\n";
}

/** @} */
