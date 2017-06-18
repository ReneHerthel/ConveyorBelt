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
 * @brief      Service header declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#ifndef HEIGHTMEASUREMENTSERVICE_H_
#define HEIGHTMEASUREMENTSERVICE_H_

/*
 * @brief Access macros for the calibrationDataPtr.
 * @{
 */
#define DELTA_VAL (calibrationDataPtr->delta)
#define REF_HEIGHT_VAL (calibrationDataPtr->refHeight)
#define HOLE_HEIGHT_VAL (calibrationDataPtr->holeHeight)
#define SURFACE_HEIGHT_VAL (calibrationDataPtr->surfaceHeight)
#define LOW_HEIGHT_VAL (calibrationDataPtr->lowHeight)
#define HIGH_HEIGHT_VAL (calibrationDataPtr->highHeight)
#define INVALID_HEIGHT_VAL (calibrationDataPtr->invalidHeight)

#define WINDOW_SIZE 20
/** @} */

#include "HeightContext.h"

#include "TimerService.h"

#include <stdint.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <thread>
#include <sys/netmgr.h>

/*
 * @brief Fast forwarding the HeightContext class.
 */
class HeightContext;

using namespace HeightMeasurement;

class HeightMeasurementService {
public:
    /*
     * @brief The calibration data, which is initialized at the begining once.
     */
    struct CalibrationData {
        int16_t delta;         /*< The range, which makes the data still valid.*/
        int16_t refHeight;     /*< The height of the belt.*/
        int16_t holeHeight;    /*< The height of the puck's hole.*/
        int16_t surfaceHeight; /*< The height of the puck's top.*/
        int16_t highHeight;    /*< The height of the Bit-coded puck's 1.*/
        int16_t lowHeight;     /*< The height of the Bit-coded puck's 0.*/
        int16_t invalidHeight; /*< The height of the Invalid puck.*/
    };

    /*
     * @brief The constructor with two channels and the calibrated data.
     *
     * @param[receive_chid] The channel id for the receive channel.
     * @param[send_chid] The channel id for the sending channel.
     * @param[*calibrationDataPtr] A pointer to the calibrated data.
     */
    HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr);

    /*
     * @brief The default virtual destructor.
     */
    virtual ~HeightMeasurementService();

    /*
     * @brief Starts the measuring thread, by creating a new thread.
     */
    void startMeasuring();

    /*
     * @brief Stops the measuring thread.
     */
    void stopMeasuring();

    /*
     * @brief Get the highest measured height from the measuring thread.
     *
     * @return returns the highest height (->lowest value).
     */
    uint16_t getHighestHeight();

private:
    TimerService timer;
    /*
     * @brief the heighest measured height
     */
    uint16_t highestHeight;

    /*
     * @brief A pointer to the statemachine object.
     */
    HeightContext *stateMachine;

    /*
     * @brief A pointer to the calibrated data.
     */
    CalibrationData *calibrationDataPtr;

    /*
     * @brief The "receive-channel-id", where the state machine listen on it.
     */
    int receive_chid;

    /*
     * @brief Controlls the superloop of the measuring thread from the outside.
     */
    volatile bool measurementIsRunning;

    /*
     * @brief Controlls the  superloop of the statemachine thread from the outside.
     */
    volatile bool statemachineIsRunning;

    /*
     * @brief The superloop task of the measurement-thread.
     */
    void measuringTask(int measuring_chid);

    /*
     * @brief Check in which range the current measured data is.
     *
     * @param[*state] A pointer to the current state of the measuring.
     * @param[data] The current measured data from the hal.
     */
    void dataInRange(Signal *state, uint16_t data);

    /*
     * @brief The superloop task of the statemachine-thread.
     */
    void stateMachineTask(int receive_chid);

    /*
     * @brief The measurement thread.
     */
    std::thread measurementThread;

    /*
     * @brief The statemachine thread.
     */
    std::thread stateMachineThread;
};

#endif /* HEIGHTMEASUREMENTSERVICE_H_ */
/** @} */
