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

/*
 * @brief The length of the buffer.
 *
 * @description NOTE: This needs to be defined here, otherwise we need object
 *                    serialization for the buffer.
 */
#define BUFFER_LENGTH    (65536) // 2^16

    class RecordBuffer : public IRecordBuffer {
    public:
        /*
         * @brief Constructor, which creates a new buffer on the heap.
         */
        explicit RecordBuffer()
            :    m_length(BUFFER_LENGTH)
            ,    m_read(0)
            ,    m_write(0)
            ,    m_count(0)
            ,    m_buffer()
        {
            // Nothing todo so far.
        }

        /*
         * @brief Copy constructor.
         */
        explicit RecordBuffer(const RecordBuffer & other)
            :    m_length(other.m_length)
            ,    m_read(other.m_read)
            ,    m_write(other.m_write)
            ,    m_count(other.m_count)
            ,    m_buffer(other.m_buffer)
        {
            // Nothing todo so far.
        }

        /*
         * @brief The destructor, which deletes the buffer from the heap.
         */
        ~RecordBuffer()
        {
            // Nothing todo so far.
        }

        int write(record_t record);
        int read(record_t *record);
        int readFromIndex(record_t * record, const int index);

    private:
        /*
         * @brief The size or length of the buffer.
         */
        size_t m_length;

        /*
         * @brief The read (tail) index of the buffer.
         */
        size_t m_read;

        /*
         * @brief The write (head) index of the buffer.
         */
        size_t m_write;

        /*
         * @brief Counts the amount of values in the buffer.
         */
        size_t m_count;

        /*
         * @brief The buffer which contains all data.
         */
        record_t m_buffer[BUFFER_LENGTH];

        // TODO: A reference to the PuckManager.
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_RECORDBUFFER_H_ */
/** @} */
