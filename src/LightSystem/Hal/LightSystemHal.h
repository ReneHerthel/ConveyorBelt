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
#include "enum.h"
#include <iostream>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <cstdlib>
#include <thread>
#include <chrono>

/** Change green light */
#define GREEN_SHIFT		5
/** Change yellow light */
#define YELLOW_SHIFT	6
/** Change red light */
#define RED_SHIFT		7
/** Change all light */
#define ALL_SHIFT		(GREEN_SHIFT | YELLOW_SHIFT | RED_SHIFT)
/** TODO: Explain purpose */
#define CTRL_REG_GROUP0     0x303
/*
 * PORT A : OUTPUT
 * PORT B : INPUT
 * PORT C Lo : OUTPUT
 * PORT C Hi : INPUT
 * Mode Select : 00
 */
/** TODO: Explain purpose */
#define DEFAULT_PORTS_SETTINGS 0x8A

/* TODO: Move Port_ADDRS to global header */
#define PORTA_ADDR 0x300
#define PORTB_ADDR 0x301
#define INPUT_MASK 0x01

namespace HAL {
    class LightSystemHal: public BLightSystem {
        public:
            void lightOn(Color color);
            void lightOff(Color color);
    };
}

#endif
