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

#include "ConveyorBeltHal.h"
#include "HWaddresses.h"
#include "HWaccess.h"

/*
 * TODO: kommentare
 */


BConveyorBelt::~BConveyorBelt() {
	// Nothing todo so far.
}

void ConveyorBeltHal::nextState(ConveyorBeltState state) {
	int bitMask = ENGINE_REG_MASK;

	// Clear all corresponding engine bits.
	out8(PORTA_REG_ADDR, (in8(PORTA_REG_ADDR) & ~(bitMask)));

	switch (state) {
		case RIGHTFAST:
			bitMask = ENGINE_RIGHTFAST_REG_MASK;
			break;
		case RIGHTSLOW:
			bitMask = ENGINE_RIGHTSLOW_REG_MASK;
			break;
		case LEFTFAST:
			bitMask = ENGINE_LEFTFAST_REG_MASK;
			break;
		case LEFTSLOW:
			bitMask = ENGINE_LEFTSLOW_REG_MASK;
			break;
		case STOP:
			bitMask = ENGINE_STOP_REG_MASK;
			break;
		default:
			bitMask = 0x00; // Don't do anything.
			break;
	}

	// Set the new bit-mask if it is not zero.
	if (bitMask != 0) {
		out8(PORTA_REG_ADDR, (in8(PORTA_REG_ADDR) | bitMask));
	}
}

/** @} */
