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

#include <stdlib.h> // malloc

namespace rec {

#define BUFFER_NULL    (-1)
#define BUFFER_EMPTY   (-2)
#define BUFFER_SUCCESS (0)

int RecordBuffer::write(record_t record)
{
    if (_write >= _size) {
        _write = 0;
    }

    // Move the _read forward by one.
    if (_write == _read) {
        _read++;
    }

    _buffer[_write] = record;
    _write++;
    _count++;

    if (_count > _size) {
        _count = _size;
    }

    return BUFFER_SUCCESS;
}

int RecordBuffer::read(record_t *record)
{
    if (_read >= _size) {
        _read = 0;
    }

    // Read, when there are values. And decrement, when read was successfully.
    if (_count > 0) {
        *record = _buffer[_read];
        _count--;
    }

    // Only increment, when there are not already readed fields left.
    if (    (_read + 1 == _write)    ||    (_write == 0 && _read + 1 >= _size)    ) {
        return BUFFER_EMPTY;
    }
    else {
        _read++;
    }

    return BUFFER_SUCCESS;
}

} /* namespace rec */

/** @} */
