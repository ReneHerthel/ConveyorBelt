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

#include "PulseMessageReceiverService.h"
#include "PulseMessageSenderService.h"

#include <thread>

namespace rec {
    class EmbeddedRecorder : public IEmbeddedRecorder {
    public:
        /*
         * @brief Constructor with the length of the buffer.
         *
         * @param[bufferLength] TODO
         */
        EmbeddedRecorder(const int bufferLength);

        /*
         * @brief Constructor with buffer length and the chid to send.
         *
         * @param[bufferLength] TODO
         * @param[chid] TODO
         */
        EmbeddedRecorder(const int bufferLength, const int chid);

        /*
         * @brief Default destructor.
         */
        ~EmbeddedRecorder();

        /*
         * @brief The super loop of the thread.
         */
        void control();

        void showRecordedData();
        void playRecordedData();
        void saveRecordedData();
        void loadRecordedData();

        /*
         * @brief Control flag, true will endless run the thread, false ends it.
         */
        bool isRunning;

    private:
        /*
         * @brief TODO
         */
        void importData();

        /*
         * @brief TODO
         */
        void exportData();

        /*
         * @brief The thread where the recorder is running and controlling all.
         */
        std::thread controller;

        /*
         * @brief The reference to the buffer.
         */
        RecordBuffer *recordBuffer;

        /*
         * @brief A reference to the receiver.
         */
        rcv::PulseMessageReceiverService *receiver;

        /*
         * @brief A reference to the sender.
         */
        PulseMessageSenderService *sender;

        /*
         * @brief TODO: A reference to the file descriptor.
         */

        /*
         * @brief TODO: A reference to the data visualizer.
         */
    };
}

#endif /* SRC_EMBEDDEDRECORDER_EMBEDDEDRECORDER_H_ */
/** @} */
