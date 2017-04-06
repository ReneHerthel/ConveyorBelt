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
  * @brief      Function declaration of the LED component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "LED.h"
#include <iostream>

HAL::LED::LED(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: Initialize port an pin at the registers.
}

HAL::LED::~LED() {
	// Nothing todo so far.
}

void HAL::LED::on() {
	// TODO: Set the corresponding bit in the IO register.
}

void HAL::LED::off() {
	// TODO: Set the corresponding bit in the IO register.
}

/** @} */
