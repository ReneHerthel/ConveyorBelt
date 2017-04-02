/*
 * Copyright (C) 2017 René Herthel
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
 * @author     René Herthel <rene.herthel@haw-hamburg.de>
 */

#include "LED.h"
#include <iostream>

HAL::LED::LED() {
	// Nothing todo so far.
}

HAL::LED::LED(const int port, const int pin) 
	: port_(port)
	, pin_(pin)
{
	// TODO: Initialize port an pin at the registers.
}

HAL::LED::~LED() {
	// Nothing todo so far.
}

void HAL::LED::On() {
	// TODO: Set the corresponding bit in the IO register.
}

void HAL::LED::Off() {
	// TODO: Set the corresponding bit in the IO register.
}

/** @} */
