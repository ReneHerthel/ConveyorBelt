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
#include "HWdefines.h"

#include <iostream>
#include <chrono>
#include <thread>

void TestHeightMeasurement::startTest() {
    std::cout<<"[TestHeightMeasurement] Start:"<<std::endl;

    HeightMeasurementHal hal;
    int16_t data = 0;
    hal.read(data);

    std::cout<<"[TestHeightMeasurement] Hal data: "<<(int)data<<std::endl;

    std::cout<<"[TestHeightMeasurement] Context: "<<(int)data<<std::endl;

    // Use the chid in the constructor.
    HeightContext context(9);

    context.process(HeightContext::START);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    context.process(HeightContext::HOLE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    context.process(HeightContext::SURFACE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    context.process(HeightContext::REF_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout<<"[TestHeightMeasurement] Done."<<std::endl;
}

/** @} */
