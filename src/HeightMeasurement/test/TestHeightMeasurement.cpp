/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Test function declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestHeightMeasurement.h"

#include "HeightMeasurementHal.h"
#include "HWdefines.h"

#include <iostream>
#include <stdint.h>


void TestHeightMeasurement::startTest() {


	// MAKE SURE YOUR THREAD HAS I/O PERMISSIONS.


	std::cout<<"[TestHeightMeasurement] start.."<<std::endl;

	std::cout<<"[TestHeightMeasurement] read.."<<std::endl;

	HeightMeasurementHal hal;
	int16_t data = 0;
	hal.read(data);

	std::cout<<"[TestHeightMeasurement] output: "<<(int)data<<std::endl;
}
/** @} */
