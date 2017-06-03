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

namespace rec {

EmbeddedRecorder::EmbeddedRecorder(const int bufferLength, const int sendChid)
    :    _recordBuffer(new RecordBuffer(bufferLength))
    :    _sendChid(sendChid);
{
    // Nothing todo so far.
}

EmbeddedRecorder::~EmbeddedRecorder() {
    delete recordBuffer; // Delete from heap.
}

void EmbeddedRecorder::showRecordedData() {
    // TODO Print the current buffer content to the terminal
}

void EmbeddedRecorder::playRecordedData() {
    // TODO Create a thread, which sends the current buffer to the maincontroller.
}

void EmbeddedRecorder::saveRecordedData() {
    // TODO Save the current buffer via BufferFileStreamer into a file.
}

void EmbeddedRecorder::loadRecordedData() {
    // TODO Load via BufferfileStreamer from file to buffer.
}

} /* namespace rec */

/** @} */
