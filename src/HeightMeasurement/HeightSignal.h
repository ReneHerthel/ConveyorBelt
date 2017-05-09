/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      HeightSignal header declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#ifndef HEIGHTSIGNAL_H_
#define HEIGHTSIGNAL_H_

#include <stdint.h>

/*
 * @brief A specific structure for pulse messages.
 */
typedef union {
    struct {
        uint8_t ID : 5;  // The SignalID.
        union {
            struct {
                uint8_t BIT0 : 1;
                uint8_t BIT1 : 1;
                uint8_t BIT2 : 1;
            };
            uint8_t pattern;  // The whole bit-pattern.
        };
    };
    uint8_t value;  // The whole structure as a value.
} signal_t;

/*
 * @brief The ID's of all available signals send from the statemachine to the con.
 */
enum SignalID {
    INVALID_ID,
    TIMEOUT_ID,
    NORMAL_ID,
    FLIPPED_ID,
    PATTERN_ID,
    UNEXPECTED_ID,
};

/*
 * @brief This enum describes the signals to be processed.
 */
enum Signal {
    INVALID,
    TIMEOUT,
    START,
    WAIT,
    RESUME,
    HOLE_HEIGHT,
    SURFACE_HEIGHT,
    REF_HEIGHT,
    PATTERN_READ,
    LOW_HEIGHT,
    HIGH_HEIGHT
};

#endif /* HEIGHTSIGNAL_H_ */
/** @} */
