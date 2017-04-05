// =====================================================================================
// LightSystemHAL.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMHAL_H
#define LIGHTSYSTEMHAL_H

#include "enum.h"
#include <iostream>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <cstdlib>
#include <thread>
#include <chrono>

#define GREEN_SHIFT		5
#define YELLOW_SHIFT	6
#define RED_SHIFT		7
#define CTRL_REG_GROUP0     0x303
/*
 * PORT A : OUTPUT
 * PORT B : INPUT
 * PORT C Lo : OUTPUT
 * PORT C Hi : INPUT
 * Mode Select : 00
 */
#define DEFAULT_PORTS_SETTINGS 0x8A

#define PORTA_ADDR 0x300
#define PORTB_ADDR 0x301
#define INPUT_MASK 0x01
//TODO  exclude Port_ADDRS in an other global header
namespace HAL {
    class LightSystemHAL : public BLightSystem {
        public:
            void lightOn(Color color);
            void lightOff(Color color);

    };
}

#endif
