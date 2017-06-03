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
 * @brief      The interface of the BufferFileStreamer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_IBUFFERFILESTREAMER_H_
#define SRC_EMBEDDEDRECORDER_IBUFFERFILESTREAMER_H_

#include "RecordBuffer.h"

namespace rec {

    class IBufferFileStreamer {
    public:
        /*
         * @brief Export the given buffer into a file.
         *
         * @param[buffer] A reference to the exported buffer.
         */
        virtual void exportBuffer(RecordBuffer *buffer) = 0;

        /*
         * @brief Imports the given buffer from file.
         *
         * @param[buffer] A reference to the imported buffer.
         */
        virtual void importBuffer(RecordBuffer *buffer) = 0;
    }

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_IBUFFERFILESTREAMER_H_ */
/** @} */
