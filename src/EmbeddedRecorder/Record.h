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
#include <time.h>

namespace rec {

    /*
     * @brief This struct defines a single record.
     */
    typedef struct {
        uint8_t code;       /*< The code of a pulse message.*/
        timespec timestamp;   /*< The timestamp of this record.*/
        uint32_t value;     /*< The value of the pulse message.*/
    } record_t;

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_RECORD_H_ */
/** @} */
