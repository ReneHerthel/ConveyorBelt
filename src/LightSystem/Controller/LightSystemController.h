/**
 *       @file  LightSystemController.h
 *      @brief  Processes messages and delegate to hardware abstraction accordingly
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/07/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef LIGHTSYSTEMCONTROLLER_H
#define LIGHTSYSTEMCONTROLLER_H

#include <iostream>
#include <thread>
#include <vector>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "BLightSystem.h"
#include "LightSystemEnum.h"
#include "Logger.h"
#include "LogScope.h"

using namespace std;
using namespace HAL;

/**
 * Pair up a color and a frequency
 */
struct LightMessage {
    Color color;
    Frequency frequency;
};

class LightSystemController {
    public:

        /**
         * @brief   Constructor
         * @param   [in] chid ID of channel to receive messages on
         * @param   [in] boundary Hardware abstraction object to manipulate lights with
         */
		LightSystemController(int chid, BLightSystem* boundary);
        /**
         * @brief   Deconstructor
         *
         * Stops the threads by toggling control member. Control thread
         * is unblocked by sending in band message LIGHT_SYSTEM_STOP.
         * After returning the threads are destroyed.
         */
		~LightSystemController();
    private:
		volatile bool isRunning; /**< @brief Control variable to start or stop both threads */
		volatile Frequency frequency; /** Control variable to pass blinking frequency to taskThread */
		volatile Color color; /** Control variable to pass light color to taskThread */
		int chid; /** Channel ID */
        BLightSystem* boundary; /** Hardware abstraction object */
        /* TODO: Ask @pareigis if lights have to blink independently */
        /**
         * @brief  Thread function to set color and frequency with boundary according to color and frequency
         * @return Always returns 1 on stop
         *
         * Reaction time to updates on control variables is one period
         * of frequency
         */
        int task(void); 
        /**
         * @brief  Thread function to set color and frequency with boundary according to color and frequency
         * @param  [in] chid Set channel ID to receive messages on
         * @return Always returns 1 on stop
         */
        int control(int);

        thread* controlThread;
        thread* taskThread;
};

#endif
