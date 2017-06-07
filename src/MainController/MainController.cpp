/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    main controller
 * @{
 *
 * @brief      Function declaration of the main controller.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include <thread>

MainController::MainController()
    :    m_receiver(new m_receiver())
    ,    m_messageInterpreterIsRunning(true)
{
    m_chid = m_receiver->newChannel();
    m_messageInterpreter = std::thread(&MainController::messageInterpreter, this);
}

MainController::~MainController()
{
    m_messageInterpreterIsRunning = false;
}

void MainController::messageInterpreter()
{
    while (m_messageInterpreterIsRunning) {
        rcv::msg_t msg = m_receiver->receivePulseMessage();
        // m_embeddedRecorder->writeValuesIntoBuffer(msg.code, msg.value);
        // TODO: Interpret the message.
    }
}

/** @} */
