/*
 * Copyright (C) 2017 Ren� Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    sorting_switch
 * @{
 *
 * @brief      Functionality of the SortingSwitch component
 *
 * @author     Ren� Herthel <rene.herthel@haw-hamburg.de>
 */

#include "SortingSwitch.h"
#include <iostream>

HAL::SortingSwitch::SortingSwitch() {
	// Nothing todo so far.
}

HAL::SortingSwitch::SortingSwitch(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: Initialize port and pin the IO register.
}

HAL::SortingSwitch::~SortingSwitch() {
	// Nothing todo so far.
}

int HAL::SortingSwitch::Read() {
	// TODO: Read from the IO register.
	return -1;
}

/** @} */
