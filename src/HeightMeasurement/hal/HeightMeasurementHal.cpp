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
 * @brief      Hal Function declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#include "HeightMeasurementHal.h"
#include "HWaccess.h"
#include "HWdefines.h"
#include <unistd.h>

/*
 * @brief Describes the size of one byte in decimal.
 */
#define BYTE               8

/*
 * @brief The distance laser sensor only has a resolution of 12-bit.
 */
#define RESOLUTION_MASK   0x0FFF

/*
 * @brief The amount of time 't' to wait to complete the conversion.
 */
#define WAIT_TIME         10

void HeightMeasurementHal::read(int16_t &data) {

	// Send an opcode to start the conversion.
	out8(PORT_ADDR_AIO + HEIGHT_MEASUREMENT_OFFSET_LOW_BYTE, HEIGHT_MEASUREMENT_START_CODE);

	// Wait a few microseconds to complete the conversion
	usleep(WAIT_TIME);

	// Read the low byte
	data = in8(PORT_ADDR_AIO + HEIGHT_MEASUREMENT_OFFSET_LOW_BYTE);

	// Read the high byte and shift it 8 bits to left.
	data |= (in8(PORT_ADDR_AIO + HEIGHT_MEASUREMENT_OFFSET_HIGH_BYTE) << BYTE);

	// Mask it to the 12-bit resolution of the distance laser.
	data &= RESOLUTION_MASK;
}

/** @} */
