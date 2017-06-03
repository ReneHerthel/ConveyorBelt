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

EmbeddedRecorder::EmbeddedRecorder(const int bufferLength, const int sendChid)
    :    _recordBuffer(new RecordBuffer(bufferLength))
    ,    _sendChid(sendChid)
    ,    _bufferFileStreamer(new BufferFileStreamer())
{
    // Nothing todo so far.
}

EmbeddedRecorder::~EmbeddedRecorder()
{
    delete _recordBuffer;
    delete _bufferFileStreamer;
}

void EmbeddedRecorder::writeRecordIntoBuffer(record_t record)
{
    _recordBuffer->write(record);
}

void EmbeddedRecorder::showRecordedData()
{
    int ret = 0;

    // Copy the buffer, so the original buffer will not be effected.
    RecordBuffer copyOfBuffer = _recordBuffer;

    // Print the buffer content to the terminal, while the buffer is not empty.
    while (ret >= 0) {
        record_t record = NULL;

        ret = copyOfBuffer->read(record);

        if (ret >= 0 && record != NULL) {
            std::cout << "time: " << record.timestamp << "  -  Code: " record.code << "  -  value: " << record.value << std::endl;
        }
    }
}

void EmbeddedRecorder::playRecordedData()
{
    // This object works for itself.
    _threadRecordSender = new ThreadRecordSender();
}

void EmbeddedRecorder::saveRecordedData()
{
    _bufferFileStreamer->exportBuffer(_recordBuffer);
}

void EmbeddedRecorder::loadRecordedData()
{
    _bufferFileStreamer->importBuffer(_recordBuffer);
}

} /* namespace rec */

/** @} */
