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

#include "IRecordBuffer.h"

#include <stdlib.h>
#include <stdint.h>

namespace rec {
    class RecordBuffer : public IRecordBuffer {
    public:
        /*
         * @brief TODO
         */
        explicit RecordBuffer(const size_t size)
            :    _size(size)
            ,    _read(0)
            ,    _write(0)
        {
            _buffer = new record_t[size];
        }

        /*
         * @brief TODO
         */
        ~RecordBuffer()
        {
            delete[] _buffer;
        }

        /*
         * @brief TODO
         *
         * @return 0 < on error.
         */
        int write(record_t record);

        /*
         * @brief TODO
         *
         * @return 0 < on error.
         */
        int read(record_t *record);

    private:
        /*
         * @brief TODO
         */
        record_t * _buffer;

        /*
         * @brief TODO
         */
        size_t _size;

        /*
         * @brief TODO
         */
        size_t _read;

        /*
         * @brief TODO
         */
        size_t _write;

        /*
         * @brief TODO
         */
        size_t _count;
    };
}

#endif /* SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_ */
/** @} */
