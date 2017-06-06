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

#include "TestHeightMeasurementStatemachine.h"
#include "HeightContext.h"

#include <sys/neutrino.h>
#include <iostream>

SETUP(TestHeightMeasurementStatemachine) {
    REG_TEST(test1, 1, "Test the Normal type");
    REG_TEST(test2, 2, "Test the Flipped type");
    REG_TEST(test3, 3, "Test the Invalid type");
    REG_TEST(test4, 4, "Test the Bitcoded 101 type");
    REG_TEST(test5, 5, "Test the Bitcoded 010 type");
    return 1;
}

BEFORE_TC(TestHeightMeasurementStatemachine) {
    // Empty.
    return 1;
}

AFTER_TC(TestHeightMeasurementStatemachine) {
    // Empty.
    return 1;
}

BEFORE(TestHeightMeasurementStatemachine) {
    // Empty.
    return 1;
}

AFTER(TestHeightMeasurementStatemachine) {
    // Empty.
    return 1;
}

TEST_IMPL(TestHeightMeasurementStatemachine, test1) {
    int chid = ChannelCreate_r(0);

    HeightContext* stateMachine;

    if (chid < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Channel creation failed" << std::endl;
    }

    stateMachine = new HeightContext(chid, nullptr);

    std::cout << "[TestHeightMeasurementStatemachine] Test the Normal type now" << std::endl;

    stateMachine->process(START);
    stateMachine->process(HOLE_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(REF_HEIGHT);

    struct _pulse pulse;

    int err = MsgReceive_r(chid, &pulse, sizeof(_pulse), NULL);

    if (err < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Error on MsgReceive_r" << std::endl;
    }

    std::cout << "[TestHeightMeasurementStatemachine] Received pulse: " << pulse.value.sival_int << "\n" <<  std::endl;

    int signal = pulse.value.sival_int;

    if (signal == 2) {
    	  return TEST_PASSED;
    }

    return TEST_FAILED;
}

TEST_IMPL(TestHeightMeasurementStatemachine, test2) {
    int chid = ChannelCreate_r(0);

    HeightContext* stateMachine;

    if (chid < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Channel creation failed" << std::endl;
    }

    stateMachine = new HeightContext(chid, nullptr);

    std::cout << "[TestHeightMeasurementStatemachine] Test the Flipped type now" << std::endl;

    stateMachine->process(START);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(REF_HEIGHT);

    struct _pulse pulse;

    int err = MsgReceive_r(chid, &pulse, sizeof(_pulse), NULL);

    if (err < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Error on MsgReceive_r" << std::endl;
    }

    std::cout << "[TestHeightMeasurementStatemachine] Received pulse: " << pulse.value.sival_int << "\n" <<  std::endl;

    int signal = pulse.value.sival_int;

    if (signal == 3) {
    	  return TEST_PASSED;
    }

    return TEST_FAILED;
}

TEST_IMPL(TestHeightMeasurementStatemachine, test3) {
    int chid = ChannelCreate_r(0);

    HeightContext* stateMachine;

    if (chid < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Channel creation failed" << std::endl;
    }

    stateMachine = new HeightContext(chid, nullptr);

    std::cout << "[TestHeightMeasurementStatemachine] Test the Invalid type now" << std::endl;

    stateMachine->process(START);
    stateMachine->process(INVALID);

    struct _pulse pulse;

    int err = MsgReceive_r(chid, &pulse, sizeof(_pulse), NULL);

    if (err < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Error on MsgReceive_r" << std::endl;
    }

    std::cout << "[TestHeightMeasurementStatemachine] Received pulse: " << pulse.value.sival_int << "\n" <<  std::endl;

    int signal = pulse.value.sival_int;

    if (signal == 0) {
    	  return TEST_PASSED;
    }

    return TEST_FAILED;
}

TEST_IMPL(TestHeightMeasurementStatemachine, test4) {
    int chid = ChannelCreate_r(0);

    HeightContext* stateMachine;

    if (chid < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Channel creation failed" << std::endl;
    }

    stateMachine = new HeightContext(chid, nullptr);

    std::cout << "[TestHeightMeasurementStatemachine] Test the 101 type now" << std::endl;

    stateMachine->process(START);
    stateMachine->process(HIGH_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(LOW_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(HIGH_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(REF_HEIGHT);

    struct _pulse pulse;

    int err = MsgReceive_r(chid, &pulse, sizeof(_pulse), NULL);

    if (err < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Error on MsgReceive_r" << std::endl;
    }

    signal_t s = {.value = pulse.value.sival_int};

    std::cout << "[TestHeightMeasurementStatemachine] Received pulse: " << (int)s.ID << " - " << (int)s.BIT0 << (int)s.BIT1 << (int)s.BIT2 << "\n" <<  std::endl;

    if (((int)s.ID == 4) && ((int)s.BIT0 == 1) && ((int)s.BIT1 == 0) && ((int)s.BIT2 == 1))
    {
    	  return TEST_PASSED;
    }

    return TEST_FAILED;
}

TEST_IMPL(TestHeightMeasurementStatemachine, test5) {
    int chid = ChannelCreate_r(0);

    HeightContext* stateMachine;

    if (chid < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Channel creation failed" << std::endl;
    }

    stateMachine = new HeightContext(chid, nullptr);

    std::cout << "[TestHeightMeasurementStatemachine] Test the 010 type now" << std::endl;

    stateMachine->process(START);
    stateMachine->process(LOW_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(HIGH_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(LOW_HEIGHT);
    stateMachine->process(SURFACE_HEIGHT);
    stateMachine->process(REF_HEIGHT);

    struct _pulse pulse;

    int err = MsgReceive_r(chid, &pulse, sizeof(_pulse), NULL);

    if (err < 0) {
        std::cout << "[TestHeightMeasurementStatemachine] Error on MsgReceive_r" << std::endl;
    }

    signal_t s = {.value = pulse.value.sival_int};

    std::cout << "[TestHeightMeasurementStatemachine] Received pulse: " << (int)s.ID << " - " << (int)s.BIT0 << (int)s.BIT1 << (int)s.BIT2 << "\n" << std::endl;

    if (((int)s.ID == 4) && ((int)s.BIT0 == 0) && ((int)s.BIT1 == 1) && ((int)s.BIT2 == 0) )
    {
    	  return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
