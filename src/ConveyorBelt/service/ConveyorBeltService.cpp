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
 * @brief      Service Function declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ConveyorBeltService.h"
#include "HWdefines.h"

ConveyorBeltService::ConveyorBeltService()
	:	hal_(new ConveyorBeltHal())
{
	// Nothing todo so far.
}

ConveyorBeltService::~ConveyorBeltService() {
	// Nothing todo so far.
}

void ConveyorBeltService::ConveyorBeltChangeState(const ConveyorBeltState state) {

	// Initialize a new mask with zero.
	int mask = 0;

	/* Switch between the different states of the conveyor belt.
	 * Then set the mask with the corresponding pin information.
	 */
	switch (state) {
		case RIGHTFAST:
			mask = (1 << PIN_0);
			break;

		case RIGHTSLOW:
			mask = (1 << (PIN_0 | PIN_2));
			break;

		case LEFTFAST:
			mask = (1 << PIN_1);
			break;

		case LEFTSLOW:
			mask = (1 << (PIN_0 | PIN_1));
			break;

		case STOP:
			mask = (1 << PIN_3);
			break;
	}

	// Set the bit mask in the hal.
	hal_->setMask(mask);
}

/** @} */
