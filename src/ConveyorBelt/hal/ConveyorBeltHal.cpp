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

#include "ConveyorBeltHal.h"
#include "HWdefines.h"
#include "HWaccess.h"

BConveyorBelt::~BConveyorBelt() {
	// Nothing todo so far.
}

ConveyorBeltHal::ConveyorBeltHal(const int port)
	: port_(port)
{
	// Nothing todo so far.
}

ConveyorBeltHal::~ConveyorBeltHal()
{
	// Nothing todo so far.
}

void ConveyorBeltHal::setMask(const int mask) {
	// First clear the the corresponding bits of the register.
	out8(PORT_ADDR_A, (in8(PORT_ADDR_A) & ~(ENGINE_REG_MASK)));

	// Then set the new mask in the register.
	out8(PORT_ADDR_A, (in8(PORT_ADDR_A) | mask));
}

/** @} */
