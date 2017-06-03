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

#include "IRecordBuffer.h"
#include "RecordBuffer.h"

#include <thread>

namespace rec {

    class EmbeddedRecorder : public IEmbeddedRecorder {
    public:
        /*
         * @brief Constructor with buffer length and the chid to send.
         *
         * @param[bufferLength] The length of the buffer used by the recorder.
         * @param[chid] Channel, where the sender-thread sends pulse-messages.
         */
        EmbeddedRecorder(const int bufferLength, const int sendChid);

        /*
         * @brief Default destructor.
         */
        ~EmbeddedRecorder();

        void playRecordedData();
        void saveRecordedData();
        void loadRecordedData();
        void showRecordedData();

    private:
        /*
         * @brief The channel, where the send-thread will send to.
         */
        int _sendChid;

        /*
         * @brief The thread where the recorder is running and controlling all.
         */
        std::thread _pulseMessageSender;

        /*
         * @brief The reference to the buffer.
         */
        RecordBuffer * _recordBuffer;

        /*
         * @brief  A reference to the BufferFileStreamer.
         */
        // TODO

    }; /* class EmbeddedRecorder : public IEmbeddedRecorder */

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_EMBEDDEDRECORDER_H_ */
/** @} */
