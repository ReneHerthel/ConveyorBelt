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

#include <sys/neutrino.h>
#include <iostream>

LedService::LedService() {
	// Put new LedHal objects at the end of the vector.
	m_leds.push_back(new LedHal(PORT_ADDR_C, PIN_0)); /**< START */
	m_leds.push_back(new LedHal(PORT_ADDR_C, PIN_1)); /**< RESET */
	m_leds.push_back(new LedHal(PORT_ADDR_C, PIN_2)); /**< Q1    */
	m_leds.push_back(new LedHal(PORT_ADDR_C, PIN_3)); /**< Q2    */

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1)
	{
		std::cout << "[LedService] Can't get hardware access." << std::endl;
	}
}

void LedService::ledOn(const Led led) {
	m_leds.at(led)->set();
}

void LedService::ledOff(const Led led) {
	m_leds.at(led)->clear();
}

/** @} */
