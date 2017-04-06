/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    light_barrier
  * @{
  *
  * @brief      Function of the LightBarrier component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "LightBarrier.h"
#include <iostream>

HAL::LightBarrier::LightBarrier(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: Make an access to the port-, pin-registers.
}

HAL::LightBarrier::~LightBarrier() {
	// TODO: Reset the port-, pin-registers.
}

int HAL::LightBarrier::read()
{
	// TODO: Read from the corresponding register.
	return -1;
}

/** @} */
