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

//#include "TestEmbeddedRecorderStub.h"
#include "ISerializable.h"

#include "PuckSignal.h"

#include <stdint.h>
#include <chrono>

namespace rec {

    /*
     * @brief This struct defines a single record.
     */
    typedef struct {
        /* The code of a pulse message. */
        uint8_t code;
        /* The timestamp of this record. */
        std::chrono::time_point<std::chrono::system_clock> timestamp;
        /* The value of the pulse message. */
        uint32_t value;
        /* The serialized puck object */
        uint8_t puck[sizeof(PuckSignal::PuckType::Data)];
    } record_t;

} /* namespace rec */

#endif /* SRC_EMBEDDEDRECORDER_RECORD_H_ */
/** @} */
