/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    rec
 * @{
 *
 * @brief      The interface of the buffer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ThreadRecordSender.h"

#include "ISerializable.h"

#include "ITimer.h"
#include "TimerService.h"

#include "SerialProtocoll.h"

#include "PuckSignal.h"

#include "PulseMessageSenderService.h"
#include "CodeDefinition.h"

#include "EmbeddedRecorderSignals.h"

#include <chrono>
#include <iostream>

namespace rec {

ThreadRecordSender::ThreadRecordSender(RecordBuffer * buffer, const int chid)
    :    m_buffer(buffer)
    ,    m_chid(chid)
{
    m_client = std::thread(&ThreadRecordSender::sendWholeBuffer, this);
}

ThreadRecordSender::~ThreadRecordSender()
{
    m_client.join();
}

void ThreadRecordSender::sendWholeBuffer()
{
	// Send a start message.
    PulseMessageSenderService * sender = new PulseMessageSenderService(m_chid);
    sender->sendPulseMessage(CodeDefinition::Code::EMBEDDED_RECORDER, rec::Signals::RECORD_PLAY);
    //std::cout << "[ThreadRecordSender] send 30 | " << rec::Signals::RECORD_PLAY << std::endl;

    /* Read the first record, so it will be used
     * to get the duration between records.
     */
    record_t start;
    int ret = m_buffer->readFromIndex(&start, 0);

    std::cout << "[ThreadRecordSender] ret: " << ret << " start: " << (int)start.code << " | " << (int)start.value << std::endl;
    sender->sendPulseMessage(start.code, start.value);

    int i = 1;
    record_t next;

    // Get the next records and wind up a clock to send a pulse message.
    while (m_buffer->readFromIndex(&next, i) >= 0) {
    	windUpClockAndSend(next, start.timestamp);
        i++;
    }

    std::cout << "[ThreadSender] num of sent pulse messages " << i << std::endl;

    // Send last pulse message with information that the recorder is done playing.
    record_t fin;
    fin.code = CodeDefinition::Code::EMBEDDED_RECORDER;
    fin.value = rec::Signals::RECORD_STOP;
    windUpClockAndSend(fin, start.timestamp);
}

void ThreadRecordSender::windUpClockAndSend(record_t next, std::chrono::time_point<std::chrono::system_clock> start)
{
    ITimer * timer = new TimerService(m_chid, next.code);

    if (next.code == TRANSM_IN_CODE) {
        PuckSignal::PuckType * puck = new PuckSignal::PuckType();
        if (!puck->deserialize(&next.puck)) {
            // TODO: Error handling.
            std::cout << "[ThreadRecordSender] windUpClockAndSend() deserialize failed." << std::endl;
        }
        next.value = (int)puck;
    }

    std::cout << "[ThreadRecordSender] send code/value: " << (int)next.code << " | " << (int)next.value << std::endl;

    unsigned int milsec = std::chrono::duration_cast<std::chrono::milliseconds>(next.timestamp - start).count();
    timer->setAlarm(milsec, next.value);
}

} /* namespace rec */
/** @} */
