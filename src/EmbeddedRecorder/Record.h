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
 * @brief      The definition of a record.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_EMBEDDEDRECORDER_RECORD_H_
#define SRC_EMBEDDEDRECORDER_RECORD_H_

#include <stdint.h>

namespace rec {
    typedef struct {
        uint8_t code;    /*< The code of a pulse message.*/
        uint32_t time;   /*< The timestamp of this record.*/
        uint32_t msg;    /*< The message of the pulse message */
        // object? puck; TODO: What type is the puck? /*< The puck as object */
    } record_t;
}

#endif /* SRC_EMBEDDEDRECORDER_RECORD_H_ */
/** @} */
