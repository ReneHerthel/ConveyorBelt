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

BufferFileStreamer::BufferFileStreamer()
{
    // Nothing todo so far.
}

void BufferFileStreamer::exportBuffer(RecordBuffer * buffer)
{
    ofstream fout;

    fout.open("buffer.txt", ios::out | ios::binary | ios::trunc); // Opens the file as binary.

    // Just write the whole buffer once.
    fout.write(reinterpret_cast<char*> (&buffer), sizeof(RecordBuffer));

    // This will write every single record to the file.
    /*
    int ret = 0;

    while (ret >= 0) {
        record_t * record = NULL;

        ret = buffer->read(record);

        if (ret >= 0 && record != NULL) {
            fout.write((char *)(&record), sizeof(record));
        }
    }
    */

    fout << flush;
    fout.close();
}

void BufferFileStreamer::importBuffer(RecordBuffer * buffer)
{
    ifstream fin;

    fin.open("buffer.txt", ios::in | ios::binary);

    // Just read the whole buffer once.
    fin.read(reinterpret_cast<char*> (&buffer), sizeof(RecordBuffer));

    // This will read every single record from the file.
    /*
    while (1) {
        record_t * record = NULL;

        fin.read(reinterpret_cast<char*> (&record), sizeof(record_t));

        if (fin.eof()) {
            break;
        }

        if (record != NULL) {
            buffer->write(*record);
        }
        else {
            break;
        }
    }
    */

    fin.close();
}

} /* namespace rec */
 /** @} */
