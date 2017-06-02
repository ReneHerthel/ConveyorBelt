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

namespace rec {

#define BUFFER_NULL    (-1)
#define BUFFER_EMPTY   (-2)
#define BUFFER_SUCCESS (0)

int RecordBuffer::write(record_t record)
{
    // The read() method can increment the _write value, so check the boundaries.
    if (_write >= _size) {
        _write = 0;
    }

    // Move the _read forward by one.
    if (_write == _read) {
        _read++;
    }

    _buffer[_write] = record;
    _write++;

    if (_write >= _size) {
        _write = 0;
    }

    _count++;

    // There can not be more values in the buffer than the size of the buffer.
    if (_count > _size) {
        _count = _size;
    }

    return BUFFER_SUCCESS;
}

int RecordBuffer::read(record_t *record)
{
    // The write() method can increment the _read value, so check the boundaries.
    if (_read >= _size) {
        _read = 0;
    }

    // Only increment, when there are not already readed fields left.
    if (    (_read + 1 == _write)    ||    (_write == 0 && _read + 1 >= _size)    ) {
        return BUFFER_EMPTY;
    }

    // Read, when there are values. And decrement, when read was successfully.
    if (_count > 0) {
        *record = _buffer[_read];
        _count--;
    }

    _read++;

    if (_read >= _size) {
        _read = 0;
    }

    return BUFFER_SUCCESS;
}

} /* namespace rec */

/** @} */
