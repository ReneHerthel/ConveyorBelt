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
 * @brief      Function declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ConveyorBeltService.h"
#include "HWdefines.h"

IConveyorBelt::~IConveyorBelt() {
	// Nothing todo so far.
}

ConveyorBeltService::ConveyorBeltService()
	:	hal_(new ConveyorBeltHal(PORT_ADDR_A))
{
	// Nothing todo so far.
}

ConveyorBeltService::~ConveyorBeltService() {
	// Nothing todo so far.
}

void ConveyorBeltService::ConveyorBeltChangeState(const ConveyorBeltState state) {
	int mask = 0;

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

	hal_->setMask(mask);
}

/** @} */
