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
 * @brief      The function implementation of the BufferFileStreamer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "BufferFileStreamer.h"

#include <fstream.h>

namespace rec {

void BufferFileStreamer::exportBufferBinary(RecordBuffer * buffer)
{
    fstream file;
    // Open the file for writing, as binary and discard the content.
    file.open("/buffer.bin", ios::out | ios::binary | ios::trunc);
    // Just write the whole object to the file
    file.write((char*)buffer, sizeof(RecordBuffer));
    file.close();
}

void BufferFileStreamer::importBufferBinary(RecordBuffer * buffer)
{
    ifstream fin;
    // Open the file for reading and binary operation.
    fin.open("/buffer.bin", ios::in | ios::binary);
    fin.read((char*)buffer, sizeof(RecordBuffer));
    fin.close();
}

void BufferFileStreamer::printBufferToTxt(RecordBuffer * buffer)
{
    ofstream file ("/records.txt");
    record_t record;
    int index = 0;

    do {
        if (file.is_open()) {
            //file << "Time[" << (int)record.timestamp.tv_sec << "::" << (int)record.timestamp.tv_nsec << "] code[" << (int)record.code << "] value[" << (int)record.value << "].\n";
        	  index++;
        }
    } while (buffer->readFromIndex(&record, index) >= 0);

    file.close();
}

} /* namespace rec */
/** @} */
