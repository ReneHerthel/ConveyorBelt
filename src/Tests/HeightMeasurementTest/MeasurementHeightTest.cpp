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

#include "MeasurementHeightTest.h"
#include "TestHeightMeasurement.h"
#include "HeightMeasurementHal.h"
#include "HeightContext.h"
#include "LogScope.h"

#include <sys/neutrino.h>
#include <iostream>

SETUP(MeasurementHeightTest) {
    REG_TEST(ManualCalibration, 1, "Manual calibration of Puck heights");
    return 1;
}

BEFORE_TC(MeasurementHeightTest) {
    // Empty.
    return 1;
}

AFTER_TC(MeasurementHeightTest) {
    // Empty.
    return 1;
}

BEFORE(MeasurementHeightTest) {
    // Empty.
    return 1;
}

AFTER(MeasurementHeightTest) {
    // Empty.
    return 1;
}

TEST_IMPL(MeasurementHeightTest, ManualCalibration) {
	LOG_SCOPE

	TestHeightMeasurement thm;
	thm.startTest();

    return TEST_FAILED;
}
