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
#include "HWdefines.h"

#include "PortA.h"

SortingSwitchHal::SortingSwitchHal()
{
	// Nothing todo so far.
}

void SortingSwitchHal::set()
{
    PortA::getInstance().bitSet(1 << PIN_4);
}

void SortingSwitchHal::clear()
{
	PortA::getInstance().bitClear(1 << PIN_4);
}

/** @} */
