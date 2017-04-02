/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    metal_detector
 * @{
 *
 * @brief      Header of the MetalDetector component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "MetalDetector.h"
#include <iostream>

HAL::MetalDetector::MetalDetector() {
	// Nothing todo so far.
}

HAL::MetalDetector::MetalDetector(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: initialize port and pin in the IO register.
}

HAL::MetalDetector::~MetalDetector() {
	// TODO: Reset the port and pin in the IO register.
}

int HAL::MetalDetector::Read()
{
	// TODO: Read the IO register and return it.
	return -1;
}

/** @} */
