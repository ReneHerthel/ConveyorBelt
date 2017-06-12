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
 * @brief      The interface of the embedded recorder.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_IEMBEDDEDRECORDER_H_
#define SRC_EMBEDDEDRECORDER_IEMBEDDEDRECORDER_H_

#include "IPulseMessageReceiver.h"

#include <sys/neutrino.h>

namespace rec {

    class IEmbeddedRecorder {
    public:
    	/*
    	 * @brief Discard the old buffer and create a new one.
    	 */
    	virtual void newBuffer() = 0;

    	/*
    	 * @brief Extracts the code and value from a pulse message.
         *
         * @return The return codes of the RecordBuffer.
    	 */
    	virtual int writeMessageIntoBuffer(const rcv::msg_t message) = 0;

        /*
         * @brief Plays the recorded data.
         *
         * @description Plays the recorded data by creating a new thread, which
         *              reads the current buffer and sends pulse messages to a
         *              specific channel ID of the receiver.
         */
        virtual void playRecordedData() = 0;

        /*
         * @brief Export the current buffer into a .bin file.
         */
        virtual void saveRecordedData() = 0;

        /*
         * @brief Import a new buffer from a .bin file.
         */
        virtual void loadRecordedData() = 0;

        /*
         * @brief Write the current buffer into a .txt file.
         */
        virtual void showRecordedData() = 0;
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_IEMBEDDEDRECORDER_H_ */
/** @} */
