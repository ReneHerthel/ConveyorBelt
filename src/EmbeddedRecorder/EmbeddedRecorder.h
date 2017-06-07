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
 * @brief      The header of the embedded recorder.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_EMBEDDEDRECORDER_H_
#define SRC_EMBEDDEDRECORDER_EMBEDDEDRECORDER_H_

#include "IEmbeddedRecorder.h"

#include "IRecordBuffer.h" // Record_t
#include "RecordBuffer.h"

#include "IBufferFileStreamer.h"
#include "BufferFileStreamer.h"

#include "ThreadRecordSender.h"

#include <thread>
#include <sys/neutrino.h>

namespace rec {

    class EmbeddedRecorder : public IEmbeddedRecorder {
    public:
        /*
         * @brief Constructor with buffer length and the chid to send.
         *
         * @param[chid] Channel, where the sender-thread sends pulse-messages.
         */
        EmbeddedRecorder(const int sendChid);

        /*
         * @brief Default destructor.
         */
        ~EmbeddedRecorder();

        /*
         * @brief Write a single record into the buffer.
         */
        void writePulseIntoBuffer(struct _pulse pulse);

        void playRecordedData();
        void saveRecordedData();
        void loadRecordedData();
        void showRecordedData();

    private:
        /*
         * @brief The channel, where the send-thread will send to.
         */
        int m_sendChid;

        /*
         * @brief The thread where the recorder is running and controlling all.
         */
        ThreadRecordSender * m_threadRecordSender;

        /*
         * @brief The reference to the buffer.
         */
        RecordBuffer * m_recordBuffer;

        /*
         * @brief  A reference to the BufferFileStreamer.
         */
        BufferFileStreamer  * m_bufferFileStreamer;

    }; /* class EmbeddedRecorder : public IEmbeddedRecorder */

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_EMBEDDEDRECORDER_H_ */
/** @} */
