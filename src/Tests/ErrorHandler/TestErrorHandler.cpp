/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    error_handler
 * @{
 *
 * @brief      Test Header of the ErrorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestErrorHandler.h"
#include "ErrorHandler.h"
#include "ConveyorBeltService.h"
#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"
#include "PuckManager.h"
#include "Signals.h"
#include "LightSystemService.h"
#include "LightSystemHal.h"
#include "LightSystemController.h"

#include <iostream>
#include <thread>
#include <chrono>

SETUP(TestErrorHandler) {
    REG_TEST(test1, 1, "Test the flow of error handler");
    return 1;
}

BEFORE_TC(TestErrorHandler) {
    // Nothing todo fo far.
    return 1;
}

AFTER_TC(TestErrorHandler) {
    // Nothing todo fo far.
    return 1;
}

BEFORE(TestErrorHandler) {
    // Nothing todo fo far.
    return 1;
}

AFTER(TestErrorHandler) {
    // Nothing todo fo far.
    return 1;
}

TEST_IMPL(TestErrorHandler, test1) {
    std::cout << "[TestErrorHandler] started" << std::endl;
    int chid = ChannelCreate_r(0);

    // Request priviledges for the current thread to access hardware
    if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
        LOG_DEBUG << "Can't get Hardware access, therefore can't do anything." << std::endl;
        return EXIT_FAILURE;
    }

    ConveyorBeltService *cbs = new ConveyorBeltService();
    LightSystemHal * hal = new LightSystemHal();
    LightSystemService * service = new LightSystemService(chid);
    LightSystemController * controller = new LightSystemController(chid, hal);
    ErrorHandler * errorHandler = new ErrorHandler(chid, *cbs, service);

    // random trash signal
    PuckSignal::Signal m_sig;
    m_sig.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;

    // random puckmanager with nonsense chid
    PuckManager * puckManager = new PuckManager(chid);

    // random but needed managerReturn
    PuckManager::ManagerReturn manager;
    manager = puckManager->process(m_sig);
    this_thread::sleep_for(chrono::seconds(3));

    if (!errorHandler->hasError()) {
        errorHandler->demultiplex(manager);
    }

    this_thread::sleep_for(chrono::seconds(3));

    rcv::msg_t message;

    message.code = 5;
    message.value = interrupts::BUTTON_RESET;
    errorHandler->handleMessage(message);
    this_thread::sleep_for(chrono::seconds(3));

    message.code = 5;
    message.value = interrupts::BUTTON_START;
    errorHandler->handleMessage(message);
    this_thread::sleep_for(chrono::seconds(5));

    if (!errorHandler->hasError()) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
