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
//#include <iostream>

namespace rec {

#define BUFFER_NULL    (-1)
#define BUFFER_EMPTY   (-2)
#define BUFFER_FULL    (-3)
#define OUT_OF_BOUNDS  (-4)
#define BUFFER_SUCCESS (0)

/*
 * @brief A mutex to prevent, that more than one thread has access to the buffer.
 */
std::mutex read_write_mutex;

int RecordBuffer::write(record_t record)
{
    read_write_mutex.lock();

    if (m_write >= m_length || m_count >= m_length) {
    	read_write_mutex.unlock();
        return BUFFER_FULL;
    }

    m_buffer[m_write] = record;
    m_write++;
    m_count++;

    if (m_count > m_length) {
        m_count = m_length;
    }

    /*
    // The read() method can increment the _write value, so check the boundaries.
    if (m_write >= m_length) {
        m_write = 0;
    }

    m_buffer[m_write] = record;
    m_write++;
    m_count++;

    // Move the _read forward by one. But only when it is not empty.
    if (m_write == m_read && m_count > 0) {
        m_read++;
    }

    if (m_write >= m_length) {
        m_write = 0;
    }

    // There can not be more values in the buffer than the size of the buffer.
    if (m_count > m_length) {
        m_count = m_length;
    }
    */

    read_write_mutex.unlock();

    return BUFFER_SUCCESS;
}

int RecordBuffer::read(record_t *record)
{
    read_write_mutex.lock();

    if (m_read >= m_length) {
    	read_write_mutex.unlock();
    	return BUFFER_FULL;
    }

    if (m_read == m_write || m_count <= 0) {
    	read_write_mutex.unlock();
    	return BUFFER_EMPTY;
    }

    *record = m_buffer[m_read];
    m_read++;
    m_count--;

    // The write() method can increment the _read value, so check the boundaries.
    /*
    if (m_read >= m_length) {
        m_read = 0;
    }

    // Read, when there are values. And decrement, when read was successfully.
    if (m_count > 0) {
        *record = m_buffer[m_read];
        m_read++;
        m_count--;
    }
    else {
        read_write_mutex.unlock();
        return BUFFER_EMPTY;
    }

    if (m_read >= m_length) {
        m_read = 0;
    }
    */

    read_write_mutex.unlock();

    return BUFFER_SUCCESS;
}

int RecordBuffer::readFromIndex(record_t * record, const int index)
{
    if (index > m_length || index < 0 || index >= m_write) {
        return OUT_OF_BOUNDS;
    }

    *record = m_buffer[index];

    return BUFFER_SUCCESS;
}

} /* namespace rec */

/** @} */
