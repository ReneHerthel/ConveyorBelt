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

#include <iostream>

namespace rec {

ThreadRecordSender::ThreadRecordSender(RecordBuffer * buffer, const int chid)
    :    m_buffer(buffer)
    ,    m_sender(new PulseMessageSenderService(chid))
{
	//std::cout << "[ThreadRecordSender] ThreadRecordSender() chid: " << chid << std::endl;
    m_client = std::thread(&ThreadRecordSender::sendPulseMessagesToChid, this);
}

ThreadRecordSender::~ThreadRecordSender()
{
    // Nothing todo so far.
}

void ThreadRecordSender::sendPulseMessagesToChid()
{
	//std::cout << "[ThreadRecordSender] sendPulseMessageToChid()" << std::endl;

    int ret = 0;

    while (ret >= 0) {
        record_t record;;

        ret = m_buffer->read(&record);

        //std::cout << "[ThreadRecordSender] ret code: " << ret << std::endl;
        //std::cout << "[ThreadRecordSender] record code: " << (int)record.code << " value: " << (int)record.value << " timestamp: " << (int)record.timestamp << std::endl;

        if (ret >= 0) {
        	std::cout << "[ThreadRecordSender] send another record." << std::endl;
            m_sender->sendPulseMessage(record.code, record.value);
        }
    }

    //std::cout << "[ThreadRecordSender] sendPulseMessageToChid() end" << std::endl;

    // NOTE: The thread will be delete after the while loop.
}

} /* namespace rec */
/** @} */
