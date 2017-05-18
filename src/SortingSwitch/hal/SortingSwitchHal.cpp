/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    sortingswitch
 * @{
 *
 * @brief      Function declaration of the SortingSwitch component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "SortingSwitchHal.h"
#include "HWaccess.h"
#include "HWdefines.h"

SortingSwitchHal::SortingSwitchHal() {
	// Nothing todo so far.
}

void SortingSwitchHal::set() {
	out8(PORT_ADDR_A, (in8(PORT_ADDR_A) | (1 << PIN_4)));
}

void SortingSwitchHal::clear() {
	out8(PORT_ADDR_A, (in8(PORT_ADDR_A) & ~(1 << PIN_4)));
}

/** @} */
