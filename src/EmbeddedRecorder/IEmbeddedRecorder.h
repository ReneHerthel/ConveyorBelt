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

namespace rec {

    class IEmbeddedRecorder {
    public:
        /*
         * @brief Plays the recorded data.
         *
         * @description Plays the recorded data by creating a new thread, which
         *              reads the current buffer and sends pulse messages to a
         *              specific channel ID of the receiver.
         */
        virtual void playRecordedData() = 0;

        /*
         * @brief Read the current buffer and save it as bytestream into a file.
         */
        virtual void saveRecordedData() = 0;

        /*
         * @brief Loads a bytestream from a file and write it to the buffer.
         */
        virtual void loadRecordedData() = 0;

        /*
         * @brief Write the current buffer to the console.
         */
        virtual void showRecordedData() = 0;
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_IEMBEDDEDRECORDER_H_ */
/** @} */
