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
  * @brief      Function of the ConveyorBelt component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "ConveyorBelt.h"
#include <iostream>

HAL::ConveyorBelt::ConveyorBelt(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// TODO: Initialize port and pin in the IO register.
}

HAL::ConveyorBelt::~ConveyorBelt() {
	// TODO: Reset the port and pin in the IO register.
}

void HAL::ConveyorBelt::nextState(ConveyorBeltState state) {
	switch (state) {
	case RightFast:
		// TODO
		break;
	case RightSlow:
		// TODO
		break;
	case LeftFast:
		// TODO
		break;
	case LeftSlow:
		// TODO
		break;
	case Stopp:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}

/** @} */
