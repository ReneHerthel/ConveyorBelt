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
         * @brief Constructor, which creates a new buffer on the heap.
         *
         * @param[size] The size or amount of fields in the buffer.
         */
        explicit RecordBuffer(const size_t size)
            :    _size(size)
            ,    _read(0)
            ,    _write(0)
        {
            _buffer = new record_t[size];
        }

        /*
         * @brief The destructor, which deletes the buffer from the heap.
         */
        ~RecordBuffer()
        {
            delete[] _buffer;
        }

        int write(record_t record);
        int read(record_t *record);

    private:
        /*
         * @brief The buffer which contains all data.
         */
        record_t * _buffer;

        /*
         * @brief The size or length of the buffer.
         */
        size_t _size;

        /*
         * @brief The read (tail) index of the buffer.
         */
        size_t _read;

        /*
         * @brief The write (head) index of the buffer.
         */
        size_t _write;

        /*
         * @brief Counts the amount of values in the buffer.
         */
        size_t _count;
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_ */
/** @} */
