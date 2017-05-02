/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
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
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#include "TestHeightMeasurement.h"

#include "HeightMeasurementHal.h"
#include "HeightContext.h"
#include "HeightMeasurementService.h"
#include "HWdefines.h"

#include <iostream>
#include <chrono>
#include <thread>

#define TEST_HEIGHT_HAL             (0)
#define TEST_HEIGHT_STATEMACHINE    (0)
#define TEST_HEIGHT_SERVICE         (1)
#define SLEEP_TIME                  (1000)

void TestHeightMeasurement::startTest() {
    std::cout<<"[TestHeightMeasurement] Start:"<<std::endl;

#if TEST_HEIGHT_HAL
    std::cout<<"[TestHeightMeasurement] Testing Hal."<<std::endl;
    HeightMeasurementHal hal;
    int16_t data = 0;
    hal.read(data);
    std::cout<<"[TestHeightMeasurement] Hal data: "<<(int)data<<std::endl;
#endif /* TEST_HEIGHT_HAL */

#if TEST_HEIGHT_STATEMACHINE
    std::cout<<"[TestHeightMeasurement] Testing context: "<<(int)data<<std::endl;
    // Use the chid in the constructor.
    HeightContext context(9); // Non available chid!
    context.process(HeightContext::START);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::HOLE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::SURFACE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::REF_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
#endif /* TEST_HEIGHT_STATEMACHINE */

#if TEST_HEIGHT_SERVICE
    std::cout<<"[TestHeightMeasurement] Testing Service:"<<std::endl;
    // TODO HeightMeasurementService service(TODO);
#endif /* TEST_HEIGHT_SERVICE */

    std::cout<<"[TestHeightMeasurement] Done."<<std::endl;
}

/** @} */
