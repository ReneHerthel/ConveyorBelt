/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Hal Header declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HEIGHTMEASUREMENT_H_
#define HEIGHTMEASUREMENT_H_

#include <stdint.h>

class HeightMeasurementHal {
public:
	/*
	 * @brief Reads a signed 16 bit data value from the AIO port.
	 * @param A reference to a signed 16 bit data variable.
	 */
	void read(int16_t &data);
};

#endif /* HEIGHTMEASUREMENT_H_ */
/** @} */
