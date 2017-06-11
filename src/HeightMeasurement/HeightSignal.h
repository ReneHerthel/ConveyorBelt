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

namespace HeightMeasurement {

	/*
	 * @brief A specific structure for pulse messages.
	 */
	typedef union SIGNAL_t {

		struct {
			uint8_t ID : 5;  // The SignalID.
			uint8_t BIT0 : 1;
			uint8_t BIT1 : 1;
			uint8_t BIT2 : 1;
			uint16_t highestHeight;
		} __attribute__((packed));
		int32_t value;  // The whole structure as a value.

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
		REF_HEIGHT = 0,
		HOLE_HEIGHT = 1,
		SURFACE_HEIGHT = 2,
		LOW_HEIGHT = 3,
		HIGH_HEIGHT = 4,
		INVALID = 5,

		PATTERN_READ,
		TIMEOUT,
		START,
		WAIT,
		RESUME,
	};

}

#endif /* HEIGHTSIGNAL_H_ */
/** @} */
