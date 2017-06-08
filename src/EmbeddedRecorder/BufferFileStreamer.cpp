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

void BufferFileStreamer::exportBuffer(RecordBuffer * buffer)
{
    fstream file;
    // Open the file for writing, as binary and discard the content.
    file.open("/buffer.bin", ios::out | ios::binary | ios::trunc);
    // Just write the whole object to the file
    file.write((char*)buffer, sizeof(RecordBuffer));
    // TODO: Write the puck manager to file.
    file.close();
}

void BufferFileStreamer::importBuffer(RecordBuffer * buffer)
{
    ifstream fin;
    // Open the file for reading and binary operation.
    fin.open("/buffer.bin", ios::in | ios::binary);
    fin.read((char*)buffer, sizeof(RecordBuffer));
    // TODO: Read the puck manager from file.
    fin.close();
}

} /* namespace rec */
 /** @} */
