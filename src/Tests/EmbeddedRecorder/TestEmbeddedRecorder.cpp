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
 * @brief      Test Function of the Ringbuffer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestEmbeddedRecorder.h"

#include "IEmbeddedRecorder.h"
#include "EmbeddedRecorder.h"

#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"

SETUP(TestEmbeddedRecorder) {
    REG_TEST(test1, 1, "Test Play-, Save-, load-RecordedData");
    return 1;
}

BEFORCE_TC(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

AFTER_TC(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

BEFORCE(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

AFTER(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

TEST_IMPL(TestEmbeddedRecorder, test1)
{
    rcv::IPulseMessageReceiver * receiver = new PulseMessageReceiverService();

    int chid = receiver->newChannel();

    IEmbeddedRecorder * recorder = new EmbeddedRecorder(chid);

    struct _pulse pulse;

    pulse.value.sival_int = 24;

    recorder->writePulseIntoBuffer(pulse);
    recorder->playRecordedData();
    rcv::msg_t msg_1 = receiver->receivePulseMessage();

    recorder->writePulseIntoBuffer(pulse);
    recorder->saveRecordedData();
    recorder->playRecordedData();
    rcv::msg_t msg_2 = receiver->receivePulseMessage();

    recorder->writePulseIntoBuffer(pulse);
    recorder->saveRecordedData();
    recorder->loadRecordedData();
    recorder->playRecordedData();
    rcv::msg_t msg_3 = receiver->receivePulseMessage();

    if (msg_1.value == 24 && msg_2.value == 24 && msg_3.value == 24) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
