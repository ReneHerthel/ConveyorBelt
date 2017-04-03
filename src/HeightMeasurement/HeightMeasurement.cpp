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

#include "HeightMeasurement.h"
#include <iostream>

HAL::HeightMeasurement::HeightMeasurement(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: initialize port and pin in the IO register
}

HAL::HeightMeasurement::~HeightMeasurement() {
	// TODO: Reset the port and pin in the IO register.
}

int HAL::HeightMeasurement::readAnalog(int offset) {
	// TODO: discuss how that could work nice.
	return -1;
}

int HAL::HeightMeasurement::readPattern(int offset) {
	// TODO: discuss how that could work  nice.
	return -1;
}

/** @} */
