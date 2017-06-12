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

#include <chrono>

namespace rec {

ThreadRecordSender::ThreadRecordSender(RecordBuffer * buffer, const int chid)
    :    m_buffer(buffer)
    //,    m_sender(new PulseMessageSenderService(chid))
    ,    m_chid(chid)
{
    m_client = std::thread(&ThreadRecordSender::sendPulseMessagesToChid, this);
}

ThreadRecordSender::~ThreadRecordSender()
{
    // Nothing todo so far.
}

void ThreadRecordSender::sendPulseMessagesToChid()
{
    int ret = 0;
    int index = 0;
    ITimer * timer;

    record_t firstRecord;

    ret = m_buffer->readFromIndex(&firstRecord, 0);

    while (ret >= 0) {
        record_t record;
        ret = m_buffer->readFromIndex(&record, index);

        if (ret >= 0) {
            timer = new TimerService(m_chid, record.code);
            timer->setAlarm(duration_cast<std::chrono::milliseconds>(firstRecord.timestamp - record.timestamp).count(), record.value);
        }

        index++;
    }

    // NOTE: The thread will be delete after the while loop.
}

} /* namespace rec */
/** @} */
