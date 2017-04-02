/*
 * Copyright (C) 2017 Ren� Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    button
 * @{
 *
 * @brief      Function declaration of the button component
 *
 * @author     Ren� Herthel <rene.herthel@haw-hamburg.de>
 */

#include "Button.h"
#include <iostream>

HAL::Button::Button(){
	// Nothing todo so far.
}

HAL::Button::Button(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: Initialize port and pin in the IO register.
}

HAL::Button::~Button() {
	// TODO: Reset the port and pin in the IO register.
}

int HAL::Button::Read()
{
	// TODO: Read the IO register and return.
	return -1;
}

/** @} */