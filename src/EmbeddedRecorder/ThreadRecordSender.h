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
#include <chrono>

namespace rec {

    class ThreadRecordSender {
    public:
        /*
         * @brief Constructor.
         */
        ThreadRecordSender(RecordBuffer * buffer, const int chid);

        /*
         * @brief Default destructor.
         */
        ~ThreadRecordSender();

    private:
        /*
         * @brief The buffer from where the pulse messages are.
         */
        RecordBuffer * m_buffer;

        /*
         * @brief The client, which sends pulse messages.
         */
        std::thread m_client;

        /*
         * @brief The channel ID to send.
         */
        int m_chid;

        /*
         * @brief Sends the whole buffer to the chid.
         */
        void sendWholeBuffer();

        /*
         * @brief Use the timer wrapper to wind up a clock and send messages,
         *        When its expired.
         */
        void windUpClockAndSend(const record_t record, std::chrono::time_point<std::chrono::system_clock> start);
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_THREADRECORDSENDER_H_ */

/** @} */
