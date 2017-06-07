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

namespace rec {

ThreadRecordSender::ThreadRecordSender(RecordBuffer * buffer, const int chid)
    :    m_buffer(buffer)
    ,    m_sender(new PulseMessageSenderService(chid))
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

    while (ret >= 0) {
        record_t * record = NULL;

        ret = m_buffer->read(record);

        if (ret >= 0 && record != NULL) {
            m_sender->sendPulseMessage(record->code, record->value);
        }
    }

    // NOTE: The thread will be delete after the while loop.
}

} /* namespace rec */
/** @} */
