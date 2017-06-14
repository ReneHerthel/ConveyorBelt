/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    wrapper
 * @{
 *
 * @brief      Test Function of the PulseMessageWrapper.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestHeightMeasurement.h"
#include "HeightMeasurementHal.h"
#include "HeightContext.h"
#include "LogScope.h"

#include <sys/neutrino.h>
#include <iostream>

SETUP(TestHeightMeasurement) {
    REG_TEST(ManualCalibration, 1, "Manual calibration of Puck heights");
    return 1;
}

BEFORE_TC(TestHeightMeasurement) {
    // Empty.
    return 1;
}

AFTER_TC(TestHeightMeasurement) {
    // Empty.
    return 1;
}

BEFORE(TestHeightMeasurement) {
    // Empty.
    return 1;
}

AFTER(TestHeightMeasurement) {
    // Empty.
    return 1;
}

TEST_IMPL(TestHeightMeasurement, ManualCalibration) {
	LOG_SCOPE

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
				LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
				return TEST_FAILED;
	}

	HeightMeasurementHal hmh;
	int16_t data;
	char cntrl = 0;
	std::cout << "Measure = 'm', Quit = 'q' \n";
	do{
		hmh.read(data);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "\n Val: " << data << "\n";
		std::cout.flush();
	}while(cntrl != 'q');

    return TEST_FAILED;
}
