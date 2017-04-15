/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
  * @ingroup    led
  * @{
  *
  * @brief      Service declaration of the LED component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "LedService.h"
#include "Led.h"
#include "HWdefines.h"

#include <iostream>

ILed::~ILed() {
	// Nothing todo so far.
}

LedService::LedService() {
	// Put new LedHal objects at the end of the vector.
	halObjects_.push_back(new LedHal(PORT_ADDR_C, PIN_0)); /**< START */
	halObjects_.push_back(new LedHal(PORT_ADDR_C, PIN_1)); /**< RESET */
	halObjects_.push_back(new LedHal(PORT_ADDR_C, PIN_2)); /**< Q1    */
	halObjects_.push_back(new LedHal(PORT_ADDR_C, PIN_3)); /**< Q2    */
}

void LedService::ledOn(const Led led) {
	halObjects_.at(led)->set();
}

void LedService::ledOff(const Led led) {
	halObjects_.at(led)->clear();
}

/** @} */
