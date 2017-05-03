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
 * @brief
 */
typedef union {
	struct {
		uint8_t ID : 5;
		union {
			struct {
				uint8_t BIT0 : 1;
				uint8_t BIT1 : 1;
				uint8_t BIT2 : 1;
			};
			uint8_t pattern;
		};
	};
	uint8_t value;
} signal_t;

/*
 * @brief
 */
enum SignalID {
    INVALID,
    TIMEOUT,
    NORMAL,
    FLIPPED,
    PATTERN,
    UNEXPECTED,
};

#endif /* HEIGHTSIGNAL_H_ */
/** @} */
