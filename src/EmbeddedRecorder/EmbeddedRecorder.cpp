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

EmbeddedRecorder::EmbeddedRecorder(const int bufferLength)
    :    recordBuffer(new RecordBuffer(bufferLength))
{
    isRunning = true;
    controller = std::thread(&EmbeddedRecorder::control, this);
}

EmbeddedRecorder::EmbeddedRecorder(const int bufferLength, const int chid)
    :    recordBuffer(new RecordBuffer(bufferLength))
    ,    sender(new PulseMessageSenderService(chid))
{
    isRunning = true;
    controller = std::thread(&EmbeddedRecorder::control, this);
}

EmbeddedRecorder::~EmbeddedRecorder() {
    isRunning = false;
    delete recordBuffer;
}

void EmbeddedRecorder::showRecordedData() {
    // TODO send the recorded data to the data visualizer.
}

void EmbeddedRecorder::playRecordedData() {
    // TODO Send the whole buffered record to the chid via sender.

    int err = 0;

    while (err >= 0) { // Until the buffer is empty. (Or maybe 30 seconds are reached by timestamps)
        record_t *record = NULL;

        err = recordBuffer->pop(record);

        if (record != NULL) {
            //sender->sendPulseMessage(/*record*/);
        }
    }
}

void EmbeddedRecorder::saveRecordedData() {
    // TODO export the recorded data to the file descriptor.
}

void EmbeddedRecorder::loadRecordedData() {
    // TODO impport the data from the file descriptor.
}

void EmbeddedRecorder::control() {
    while (isRunning) {
      /* TODO's: Connect to a channel to receive messages.
       *         wait for new messages.
       *         dispatch the messages.
       *
       */
    }
}

void EmbeddedRecorder::importData() {
    // TODO
}

void EmbeddedRecorder::exportData() {
    // TODO
}

} /* namespace rec */

/** @} */
