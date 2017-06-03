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

namespace rec {

ThreadRecordSender::ThreadRecordSender(const RecordBuffer * buffer, const int chid)
    :    _buffer(buffer);
    ,    _sender(new PulseMessageSenderService(chid))
{
    _client = std::thread(&ThreadRecordSender::sendPulseMessagesToChid, this);
}

ThreadRecordSender::~ThreadRecordSender()
{
    // Nothing todo so far.
}

void ThreadRecordSender::sendPulseMessagesToChid()
{
    int ret = 0;

    while (ret >= 0) {
        record_t record = NULL;

        ret = _buffer->read(record);

        if (ret >= 0 && record != NULL) {
            sender->sendPulseMessage(record.code, record.value);
        }
    }

    // NOTE: The thread will be delete after the while loop.
}

} /* namespace rec */
/** @} */
