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

#include "Logger.h"
#include "LogScope.h"

#include <iostream>
#include <chrono>
#include <thread>

#define TEST_HEIGHT_HAL             (0)
#define TEST_HEIGHT_STATEMACHINE    (0)
#define TEST_HEIGHT_SERVICE         (0)
#define SLEEP_TIME                  (1000)

void TestHeightMeasurement::startTest() {
    LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);

#if TEST_HEIGHT_HAL
    LOG_DEBUG << "[TestHeightMeasurement] startTest() Testing Hal start\n";
    HeightMeasurementHal hal;
    int16_t data = 0;
    hal.read(data);
    LOG_DEBUG << "[TestHeightMeasurement] startTest() Hal data: " << (int)data << "\n";
    LOG_DEBUG << "TestHeightMeasurement] startTest() Testing service done\n";
#endif /* TEST_HEIGHT_HAL */

#if TEST_HEIGHT_STATEMACHINE
    LOG_DEBUG << "[TestHeightMeasurement] startTest() Testing context start\n";
    HeightContext context(9); // Non available chid!
    context.process(HeightContext::START);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::HOLE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::SURFACE_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    context.process(HeightContext::REF_HEIGHT);
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    LOG_DEBUG << "TestHeightMeasurement] startTest() Testing context done\n";
#endif /* TEST_HEIGHT_STATEMACHINE */

#if TEST_HEIGHT_SERVICE
    LOG_DEBUG << "[TestHeightMeasurement] startTest() Testing service start\n";

    int send_chid = ChannelCreate_r(0);
    if (send_chid < 0) {
    	  LOG_DEBUG << "[TestHeightMeasurement] startTest() Creating send_chid failed with: " << send_chid << "\n";
    	  return;
    }

    int receive_chid = ChannelCreate_r(0);
    if (receive_chid < 0) {
    	  LOG_DEBUG << "[TestHeightMeasurement] startTest() Creating receive_chid failed with: " << receive_chid << "\n";
    	  return;
    }

    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);
    if (coid < 0) {
    	  LOG_DEBUG << "[TestHeightMeasurement] startTest() Connect to coid failed with: " << coid << "\n";
    }

    HeightMeasurementService::CalibrationData cal;
    // Calibrated by hand!
    cal.delta = 30;
    cal.holeHeight = 3583;
    cal.refHeight = 4070;
    cal.surfaceHeight = 2545;

    HeightMeasurementService service(receive_chid, send_chid, &cal);

    // We need to send a start signal first, so the measuring will begin.
    int err = MsgSendPulse_r(coid, sched_get_priority_min(0), 0, HeightContext::START);

    if (err < 0) {
    	  LOG_DEBUG << "[TestHeightMeasurement] startTest() Sending START signal failed with: " << err << "\n";
    }

    // Structure that describes a pulse.
    struct _pulse pulse;

    // Wait for pulseMessages to simulate components, which wants to receive signals from the HeightMeasurment.
    while(1) {
        // Returns 0 on success and a negative value on error.
        int err = MsgReceivePulse_r(receive_chid, &pulse, sizeof(_pulse), NULL);

        // Do error handling, if there occurs an error.
        if (err < 0) {
            LOG_DEBUG << "[TestHeightMeasurement] startTest() Receiving pulse messages failed with: " << err << "\n";
        }

        LOG_DEBUG << "[TestHeightMeasurement] startTest() Rceived pulse message: " << pulse.value.sival_int << "\n";
    }
    LOG_DEBUG << "TestHeightMeasurement] startTest() Testing service done\n";

#endif /* TEST_HEIGHT_SERVICE */
}

/** @} */
