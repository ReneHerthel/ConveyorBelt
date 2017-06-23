/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    conveyor_belt
 * @{
 *
 * @brief      Hal Header declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */
#ifndef CONVEYORBELTHAL_H_
#define CONVEYORBELTHAL_H_

#include <stdint.h>

class ConveyorBeltHal {
public:
	/*
	 * @brief Set the corresponding mask in the port.
	 * @param A constant mask which is set in the corresponding bit.
	 */
	void setMask(const uint8_t mask);
};

#endif /* CONVEYORBELTHAL_H_ */

/** @} */
