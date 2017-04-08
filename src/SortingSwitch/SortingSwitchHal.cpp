/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    sorting_switch
  * @{
  *
  * @brief      Functionality of the SortingSwitch component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "SortingSwitchHal.h"
#include "HWaddresses.h"
#include "HWaccess.h"

#include <iostream>

#define PORTPIN 4

BSortingSwitch::~BSortingSwitch() {
	// Nothing todo so far.
}

SortingSwitchHal::SortingSwitchHal() {
	// Nothing todo so far.
}

SortingSwitchHal::~SortingSwitchHal() {
	// Nothing todo so far.
}

void SortingSwitchHal::open() {
	out8(PORTA_REG_ADDR, (in8(PORTA_REG_ADDR) | (1 << PORTPIN)));
}

void SortingSwitchHal::close() {
	out8(PORTA_REG_ADDR, (in8(PORTA_REG_ADDR) & ~(1 << PORTPIN)));
}

/** @} */
