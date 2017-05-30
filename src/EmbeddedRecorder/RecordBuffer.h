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
 * @brief      The definition of a record-buffer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_
#define SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_

#include "Record.h"

#include <stdint.h>

namespace rec {
    /*
     * @brief TODO
     */
    struct Buffer {
        record_t* data; /*< Contains all recorded data.*/
        uint8_t read;   /*< Points to the field with the oldest content.*/
        uint8_t write;  /*< Points to the next field to write.*/
        const size_t size; /*< The actual length of the buffer.*/
    };

    class RecordBuffer {
    public:
        /*
         * @brief TODO
         */
        RecordBuffer(const size_t size);

        /*
         * @brief TODO
         */
        ~RecordBuffer();

        /*
         * @brief TODO
         *
         * @return 0 < on error.
         */
        int push(record_t record);

        /*
         * @brief TODO
         *
         * @return 0 < on error.
         */
        int pop(record_t *record);

    private:
        /*
         * @brief TODO
         */
        Buffer *buffer;
    }
}

#endif /* SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_ */
/** @} */
