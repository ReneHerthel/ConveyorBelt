/**
 *       @file  LightSystemHal.h
 *      @brief  Define constants for the implementation of the hardware abstraction layer
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/06/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef LIGHTSYSTEMHAL_H
#define LIGHTSYSTEMHAL_H

#include "BLightSystem.h"
#include "Logger.h"
#include "LogScope.h"
#include "LightSystemEnum.h"
#include "PortA.h"
#include <iostream>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <cstdlib>
#include <thread>
#include <chrono>

/** Change green light */
#define GREEN_MASK (1 << 5)
/** Change yellow light */
#define YELLOW_MASK	(1 << 6)
/** Change red light */
#define RED_MASK (1 << 7)
/** Change all light */
#define ALL_MASK (GREEN_MASK|YELLOW_MASK|RED_MASK)

/* TODO: Move Port_ADDRS to global header */
#define PORTA_ADDR 0x300
#define PORTB_ADDR 0x301
#define INPUT_MASK 0x01

namespace HAL {
    class LightSystemHal: public BLightSystem {
        public:
    		LightSystemHal();
    		~LightSystemHal();
            void lightOn(Color color);
            void lightOff(Color color);
            bool checkIfPreviouslySetTo(Color newColor);
        private:
        	Color lastColor;
    };
}

#endif
