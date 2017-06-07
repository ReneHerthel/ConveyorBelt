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
 * @brief      The fucntion of the embedded recorder.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "EmbeddedRecorder.h"

#include <iostream>

namespace rec {

EmbeddedRecorder::EmbeddedRecorder(const int sendChid)
    :    m_recordBuffer(new RecordBuffer())
    ,    m_sendChid(sendChid)
    ,    m_bufferFileStreamer(new BufferFileStreamer())
{
    // Nothing todo so far.
}

EmbeddedRecorder::~EmbeddedRecorder()
{
    //delete _recordBuffer;
    //delete _bufferFileStreamer;
}

void EmbeddedRecorder::writePulseIntoBuffer(struct _pulse pulse)
{
    writeValuesIntoBuffer(pulse.code, pulse.value.sival_int);
}

void EmbeddedRecorder::writeValuesIntoBuffer(const int code, const int value)
{
    record_t * record;

    record.code = code;
    record.value = value;
    record.timestamp = -1; // TODO

    m_recordBuffer->write(record);
}

void EmbeddedRecorder::showRecordedData()
{
    // Copy the buffer, so the original buffer will not be effected.
    RecordBuffer tmp(m_recordBuffer);

    record_t * record = NULL;

    // Print the buffer content to the terminal, while the buffer is not empty.
    while ((tmp->read(record)) >= 0) {
        // TODO: Convert the timestamp into something like: "[HH::MM::SS]".
        if (record != NULL) {
            std::cout << "[" << (int)record->timestamp << "]  -  Code: " << (int)record->code << "  -  value: " << (int)record->value << std::endl;
            record = NULL;
        }
    }
}

void EmbeddedRecorder::playRecordedData()
{
    // This object works for itself.
    m_threadRecordSender = new ThreadRecordSender(m_recordBuffer, m_sendChid);
}

void EmbeddedRecorder::saveRecordedData()
{
    m_bufferFileStreamer->exportBuffer(m_recordBuffer);
}

void EmbeddedRecorder::loadRecordedData()
{
    m_bufferFileStreamer->importBuffer(m_recordBuffer);
}

} /* namespace rec */

/** @} */
