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
 * @brief      Enum declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HEIGHTMEASUREMENTSTATE_H_
#define HEIGHTMEASUREMENTSTATE_H_

enum HeightMeasurementState {
	START,
	MEASURING,
	NORMAL_PUK,
	PUK_SURFACE,
	BIT_OR_FLIPPED_PUK,
};


#endif /* HEIGHTMEASUREMENTSTATE_H_ */
/** @} */
