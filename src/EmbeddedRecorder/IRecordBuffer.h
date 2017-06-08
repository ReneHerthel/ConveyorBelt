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
 * @brief      The interface of the buffer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_IRECORDBUFFER_H_
#define SRC_EMBEDDEDRECORDER_IRECORDBUFFER_H_

#include "Record.h"

namespace rec {

    class IRecordBuffer {
    public:
        /*
         * @brief Write a new record into the buffer.
         *
         * @param[record] The record written into the buffer.
         *
         * @return 0 on success. NOTE: There are no error returns yet.
         */
        virtual int write(record_t record) = 0;

        virtual int read(record_t * record) = 0;
    };

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_IRECORDBUFFER_H_ */
/** @} */
