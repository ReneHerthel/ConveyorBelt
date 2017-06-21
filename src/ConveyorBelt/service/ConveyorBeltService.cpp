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

#include <sys/neutrino.h>
#include <iostream>

ConveyorBeltService::ConveyorBeltService()
	:	hal_(new ConveyorBeltHal())
{
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1)
	{
		std::cout << "[ConveyorBeltService] Can't get hardware access." << std::endl;
	}
}

ConveyorBeltService::~ConveyorBeltService()
{
	delete hal_;
}

void ConveyorBeltService::changeState(const ConveyorBeltState state)
{
	uint8_t mask = 0;

	/* Switch between the different states of the conveyor belt.
	 * Then set the mask with the corresponding pin information.
	 */
	switch (state) {

		case RIGHTFAST:
			mask = ENGINE_RIGHT_MASK;
			break;

		case RIGHTSLOW:
			mask = ENGINE_SLOW_MASK | ENGINE_RIGHT_MASK;
			break;

		case LEFTFAST:
			mask = ENGINE_LEFT_MASK;
			break;

		case LEFTSLOW:
			mask = ENGINE_SLOW_MASK | ENGINE_LEFT_MASK;
			break;

		case STOP:
			mask = ENGINE_STOP_MASK;
			break;
	}

	hal_->setMask(mask);
}

/** @} */
