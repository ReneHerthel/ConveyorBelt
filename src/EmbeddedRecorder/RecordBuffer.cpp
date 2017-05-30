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

RecordBuffer::RecordBuffer(const uint64_t size)
{
    buffer = new Buffer();
    buffer->data = malloc(sizeof(record_t) * size);
    buffer->write = 0;
    buffer->read = 0;
    buffer->size = size;
}

RecordBuffer::~RecordBuffer() {
    delete buffer;
}

int RecordBuffer::push(record_t record) {
    // Check if the there is a buffer.
    if (buffer == NULL) {
        return -2;
    }

    // Reset the write pointer.
    if (buffer.write >= buffer.size) {
        buffer.write = 0; // More security.
    }

    // Normaly, check if the buffer is full. But we won't do that.
    /*
    if ((buffer.write + 1 == buffer.read ) || ( buffer.read == 0 && buffer.write + 1 == buffer.size )) {
          return -1;
    }
    */

    buffer.data[buffer.write] = record;

    buffer.write += 1;

    if ((buffer.write + 1 == buffer.read)) || (buffer.read == 0 && buffer.write + 1 == buffer.size)) {
        // Actually, we overwrite the old values, but we need to know where the oldest value is.
        // So move the read index forward by one.
        buffer.read += 1;
    }

    // Reset the write pointer.
    if (buffer.write >= buffer.size) {
        buffer.write = 0;
    }

    // Everything went fine.
    return 0;
}

int RecordBuffer::pop(record_t *record) {
    // Check if there is a buffer.
    if (buffer == NULL) {
        return -1;
    }

    // Check if the buffer is empty.
    if (buffer.read == buffer.write) {
        return -2;
    }

    // Write the field of the read index into the record pointer.
    *record = buffer.data[buffer.read];

    // Increment the read index.
    buffer.read += 1;

    // Reset the read pointer.
    if (buffer.read >= buffer.size) {
        buffer.read = 0;
    }

    // Everything went fine.
    return 0;
}

} /* namespace rec */

/** @} /
