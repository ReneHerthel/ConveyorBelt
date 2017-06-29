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
//#include "TestEmbeddedRecorderStub.h"
#include "SerialProtocoll.h"
#include "IPulseMessageReceiver.h"
#include "PuckSignal.h"

#include <chrono>
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

int EmbeddedRecorder::writeMessageIntoBuffer(const rcv::msg_t message)
{
    record_t record;

    record.timestamp = std::chrono::system_clock::now();
    record.code = message.code;

    if (record.code == TRANSM_IN_CODE) {
        PuckSignal::PuckType puck = *((PuckSignal::PuckType*)message.value);
        serialized serPuck = puck.serialize();
        std::memcpy(&record.puck,serPuck.obj, serPuck.size);//puck.serialize().obj;
        //std::cout << "[writeMessageIntoBuffer] puck values: " << (int)puck.data.height1 << " & " << (int)puck.data.height2 << std::endl;
    }

    record.value = message.value;

    std::cout << "[EmbeddedRecorder] write to buffer code/value: " << (int)record.code << " | " << (int)record.value << std::endl;


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