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

//#include "TestEmbeddedRecorderStub.h"
#include "PuckSignal.h"
#include "SerialProtocoll.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>

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
    rcv::msg_t message;
    int size = 64; // Make sure the buffer size is equals in RecordBuffer.h.
    int ret_code;

    PuckSignal::PuckType * puck = new PuckSignal::PuckType(); //(PuckSignal::PuckType*)malloc(sizeof(PuckSignal::PuckType));

    std::cout << "[TestEmbeddedRecorder] init data of puck types" << std::endl;

    for (int i = 0; i < size; i++) {
        puck->data.height1 = i;
        puck->data.height2 = i+1;
    	message.value = (int)puck;
    	message.code = TRANSM_IN_CODE;
    	ret_code = recorder->writeMessageIntoBuffer(message);
    	std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "[TestEmbeddedRecorder] save" << std::endl;
    recorder->saveRecordedData();
    std::cout << "[TestEmbeddedRecorder] allocate new buffer" << std::endl;
    recorder->newBuffer();
    std::cout << "[TestEmbeddedRecorder] load" << std::endl;
    recorder->loadRecordedData();
    std::cout << "[TestEmbeddedRecorder] play" << std::endl;
    recorder->playRecordedData();

    rcv::msg_t msg;
    int amountOfReceived = 0;

    auto start = std::chrono::system_clock::now();

    std::cout << "TEST - receive messages" << std::endl;

    for (int i = 0; i < size-1; i++) {
        msg = receiver->receivePulseMessage();
        std::cout << "[TestEmbeddedRecorder] received message at " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " milliseconds" << std::endl;

        PuckSignal::PuckType puck = (*(PuckSignal::PuckType*)msg.value);

        std::cout << "[TestEmbeddedRecorder] puck values: " << (int)puck.data.height1 << " & " << (int)puck.data.height2 << std::endl;
        amountOfReceived++;
    }

    /*
    int ret_code2;

    recorder->newBuffer();

    for (int i = 0; i < size; i++) {
    	message.value = i;
    	message.code = i;
    	ret_code2 = recorder->writeMessageIntoBuffer(message);
    }

    recorder->showRecordedData();
    */

    //std::cout << "[TestEmbeddedRecorder] received messages:" << amountOfReceived << " size was: " << size << std::endl;

    if (amountOfReceived+1 == size) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
