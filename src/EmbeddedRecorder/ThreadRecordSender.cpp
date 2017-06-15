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

#include "ITimer.h"
#include "TimerService.h"

#include "TestEmbeddedRecorderStub.h"
#include "SerialProtocoll.h"

#include <chrono>

namespace rec {

ThreadRecordSender::ThreadRecordSender(RecordBuffer * buffer, const int chid)
    :    m_buffer(buffer)
    ,    m_chid(chid)
{
    m_client = std::thread(&ThreadRecordSender::sendWholeBuffer, this);
}

ThreadRecordSender::~ThreadRecordSender()
{
    // Nothing todo so far.
}

void ThreadRecordSender::sendWholeBuffer()
{
    /* Read the first record, so it will be used
     * to get the duration between records.
     */
    record_t start;
    int ret = m_buffer->readFromIndex(&start, 0);
    windUpClockAndSend(start, start.timestamp);

    int i = 0;
    record_t next;

    // Get the next records and wind up a clock to send a pulse message.
    while (m_buffer->readFromIndex(&next, i) >= 0) {
        windUpClockAndSend(next, start.timestamp);
        i++;
    }

    // NOTE: The thread will be delete after the while loop.
}

void ThreadRecordSender::windUpClockAndSend(record_t next, std::chrono::time_point<std::chrono::system_clock> start)
{
    ITimer * timer = new TimerService(m_chid, next.code);

    /* Check if there was a puck (TODO) inside the record.
     * Cast the pointer of the puck (TODO) into an integer value.
     * This must be cast into a pointer again after receiving this message.
     */
    if (next.code == TRANSM_IN_CODE) {
        next.value = (int)new TestEmbeddedRecorderStub(next.stub);
    }

    auto milsec = std::chrono::duration_cast<std::chrono::milliseconds>(next.timestamp - start).count();
    timer->setAlarm(milsec, next.value);
}

} /* namespace rec */
/** @} */
