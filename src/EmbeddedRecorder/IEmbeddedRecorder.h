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
         * @brief TODO
         */
        void showRecordedData() = 0;

        /*
         * @brief TODO
         */
        void playRecordedData() = 0;

        /*
         * @brief TODO
         */
        void saveRecordedData() = 0;

        /*
         * @brief TODO
         */
        void loadRecordedData() = 0;
    }
}

#endif /* SRC_EMBEDDEDRECORDER_IEMBEDDEDRECORDER_H_ */
/** @} */
