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
 * @brief      The interface implementation of the BufferFileStreamer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_BUFFERFILESTREAMER_H_
#define SRC_EMBEDDEDRECORDER_BUFFERFILESTREAMER_H_

#include "IBufferFileStreamer.h"

namespace rec {

    class BufferFileStreamer : public IBufferFileStreamer {
    public:
        /*
         * @brief TODO
         */
        BufferFileStreamer();

        exportBuffer(RecordBuffer * buffer);
        importBuffer(RecordBuffer * buffer);
    }

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_BUFFERFILESTREAMER_H_ */
