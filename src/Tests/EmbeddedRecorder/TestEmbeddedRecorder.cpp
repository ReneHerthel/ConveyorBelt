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

#include <iostream>

SETUP(TestEmbeddedRecorder) {
    REG_TEST(test1, 1, "Test Play-, Save-, load-RecordedData");
    return 1;
}

BEFORE_TC(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

AFTER_TC(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

BEFORE(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

AFTER(TestEmbeddedRecorder) {
    // Empty.
    return 1;
}

TEST_IMPL(TestEmbeddedRecorder, test1)
{
    rcv::IPulseMessageReceiver* receiver = new rcv::PulseMessageReceiverService();

    int chid = receiver->newChannel();

    rec::IEmbeddedRecorder * recorder = new rec::EmbeddedRecorder(chid);

    struct _pulse pulse;

    int size = 512; // Make sure the buffer size is equals in RecordBuffer.h.
    int ret_code;

    for (int i = 0; i < size; i++) {
    	pulse.value.sival_int = i;
    	ret_code = recorder->writePulseIntoBuffer(pulse);
    }

    recorder->saveRecordedData();
    recorder->loadRecordedData();
    recorder->playRecordedData();

    rcv::msg_t msg;
    int amountOfReceived = 0;

    for (int i = 0; i < size; i++) {
        msg = receiver->receivePulseMessage();
        amountOfReceived++;
    }

    int ret_code2;

    recorder->newBuffer();

    for (int i = 0; i < size; i++) {
    	pulse.value.sival_int = i;
    	pulse.code = i;
    	ret_code2 = recorder->writePulseIntoBuffer(pulse);
    }

    recorder->showRecordedData();

    if (ret_code >= 0 && ret_code2 >= 0 && amountOfReceived == size) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
