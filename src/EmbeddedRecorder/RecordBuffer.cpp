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
 * @brief      The function defintions of the record bufferfer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "RecordBuffer.h"

#include <mutex>

namespace rec {

#define BUFFER_NULL    (-1)
#define BUFFER_EMPTY   (-2)
#define BUFFER_SUCCESS (0)

/*
 * @brief A mutex to prevent, that more than one thread has access to the buffer.
 */
std::mutex read_write_mutex;

int RecordBuffer::write(record_t record)
{
    read_write_mutex.lock();

    // The read() method can increment the _write value, so check the boundaries.
    if (m_write >= m_size) {
        m_write = 0;
    }

    // Move the _read forward by one.
    if (_write == m_read) {
        _read++;
    }

    m_buffer[m_write] = record;
    m_write++;

    if (m_write >= m_size) {
        m_write = 0;
    }

    m_count++;

    // There can not be more values in the buffer than the size of the buffer.
    if (m_count > m_size) {
        m_count = m_size;
    }

    read_write_mutex.unlock();

    return BUFFER_SUCCESS;
}

int RecordBuffer::read(record_t *record)
{
    read_write_mutex.lock();

    // The write() method can increment the _read value, so check the boundaries.
    if (m_read >= m_size) {
        m_read = 0;
    }

    // Read, when there are values. And decrement, when read was successfully.
    if (_count > 0) {
        *record = m_buffer[m_read];
        m_count--;
    }
    else {
        read_write_mutex.unlock();
        return BUFFER_EMPTY;
    }

    m_read++;

    if (m_read >= m_size) {
        m_read = 0;
    }

    read_write_mutex.unlock();

    return BUFFER_SUCCESS;
}

} /* namespace rec */

/** @} */
