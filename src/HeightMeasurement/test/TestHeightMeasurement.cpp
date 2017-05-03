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
    std::cout<<"[TestHeightMeasurement] Testing context: "<<std::endl;
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
    std::cout<<"[TestHeightMeasurement] Create channels.."<<std::endl;

    int send_chid = ChannelCreate_r(0);

    if (send_chid < 0) {
    	std::cout<<"[TestHeightMeasurement] Create send_channel failed."<<std::endl;
    	return;
    }

    int receive_chid = ChannelCreate_r(0);

    if (receive_chid < 0) {
    	std::cout<<"[TestHeightMeasurement] Create receive_channel failed."<<std::endl;
    	return;
    }

    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);

    if (coid < 0) {
    	std::cout<<"[TestHeightMeasurement] connect failed."<<std::endl;
    }

    HeightMeasurementService::CalibrationData cal;
    cal.delta = 30;
    cal.holeHeight = 3583;
    cal.refHeight = 4070;
    cal.surfaceHeight =2545;

    HeightMeasurementService service(receive_chid, send_chid, &cal);

    //std::this_thread::sleep_for(std::chrono::seconds(1));

    int err = MsgSendPulse_r(coid, sched_get_priority_min(0), 0, HeightContext::START);

    if (err < 0) {
    	std::cout<<"[TestHeightMeasurement] send failed."<<std::endl;
    }

    // Structure that describes a pulse.
    struct _pulse pulse;

    while(1) {
        // Returns 0 on success and a negative value on error.
        int err = MsgReceivePulse_r(receive_chid, &pulse, sizeof(_pulse), NULL);

        // Do error handling, if there occurs an error.
        if (err < 0) {
            std::cout<<"[TestHeightMeasurement] Error on receiving pulse message."<<std::endl;
        }

        std::cout<<"[TestHeightMeasurement] received: "<<pulse.value.sival_int<<std::endl;
    }

#endif /* TEST_HEIGHT_SERVICE */

    std::cout<<"[TestHeightMeasurement] Done."<<std::endl;
}

/** @} */
