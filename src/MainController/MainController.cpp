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

#include "SerialProtocoll.h"
#include "TestEmbeddedRecorderStub.h"

#include <thread>

MainController::MainController()
    :    m_receiver(new PulseMessageReceiverService())
    ,    m_messageInterpreterIsRunning(true)
    ,    m_recorderIsPlaying(false)
{
    m_chid = m_receiver->newChannel();
    m_messageInterpreter = std::thread(&MainController::messageInterpreter, this);
    m_embeddedRecorder = new rec::EmbeddedRecorder(m_chid);
}

MainController::~MainController()
{
    m_messageInterpreterIsRunning = false;
}

void MainController::messageInterpreter()
{
    while (m_messageInterpreterIsRunning) {

        rcv::msg_t message = m_receiver->receivePulseMessage();

        // Only write into the buffer, when the EmbeddedRecorder is not playing.
        if (m_recorderIsPlaying == false) {
            m_embeddedRecorder->writeMessageIntoBuffer(message);
        }

        switch (message.code) {

            case REC_PLAY_STOP:
                m_recorderIsPlaying = false;
                break;

            case REC_PLAY_START:
                m_recorderIsPlaying = true;
                break;

            case TRANSM_IN_CODE :
                message.value =  (*(TestEmbeddedRecorderStub*)message.value);
                break;

            default:
                // TODO Error handling.
                break;

        }
    }
}

/** @} */
