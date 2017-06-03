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

#ifndef SRC_EMBEDDEDRECORDER_THREADRECORDSENDER_H_
#define SRC_EMBEDDEDRECORDER_THREADRECORDSENDER_H_

#include "RecordBuffer.h"
#include "IPulseMessageSender.h"
#include "PulseMessageSenderService.h"

#include <thread>

namespace rec {

    class ThreadRecordSender {
    public:
        /*
         * @brief Constructor.
         */
        ThreadRecordSender(const RecordBuffer * buffer, const int chid);

        /*
         * @brief Default destructor.
         */
        ~ThreadRecordSender();

        /*
         * @brief
         */
        void sendPulseMessagesToChid();

    private:
        /*
         * @brief The buffer from where the pulse messages are.
         */
        RecordBuffer * _buffer;

        /*
         * @brief The client, which sends pulse messages.
         */
        std::thread _client;

        /*
         * @brief The pulse message sender.
         */
        PulseMessageSenderService * _sender;
    }

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_THREADRECORDSENDER_H_ */

/** @} */
