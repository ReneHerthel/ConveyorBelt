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

#include <time.h>
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

void EmbeddedRecorder::newBuffer()
{
    m_recordBuffer = new RecordBuffer();
}

int EmbeddedRecorder::writePulseIntoBuffer(const struct _pulse pulse)
{
    return writeValuesIntoBuffer(pulse.code, pulse.value.sival_int);
}

int EmbeddedRecorder::writeValuesIntoBuffer(const int code, const int value)
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);

    record_t record;
    record.code = code;
    record.value = value;
    record.timestamp = time;

    return m_recordBuffer->write(record);
}

void EmbeddedRecorder::showRecordedData()
{
    m_bufferFileStreamer->printBufferToTxt(m_recordBuffer);
}

void EmbeddedRecorder::playRecordedData()
{
    /* This will actually create a thread, which sends all messages from the buffer to the main controller.
     * It will stop itself, after his function ends.
     */
    new ThreadRecordSender(m_recordBuffer, m_sendChid);
}

void EmbeddedRecorder::saveRecordedData()
{
    m_bufferFileStreamer->exportBufferBinary(m_recordBuffer);
}

void EmbeddedRecorder::loadRecordedData()
{
    m_bufferFileStreamer->importBufferBinary(m_recordBuffer);
}

} /* namespace rec */

/** @} */
