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
 * @brief      Service declaration of the SortingSwitch component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "SortingSwitchService.h"
#include "SortingSwitchHal.h"
#include "HWdefines.h"

ISortingSwitch::~ISortingSwitch() {
	// Nothing todo so far.
}

SortingSwitchService::SortingSwitchService()
	:	hal_(new SortingSwitchHal(PORT_ADDR_A))
{
	// TODO Auto-generated constructor stub

}

SortingSwitchService::~SortingSwitchService() {
	// TODO Auto-generated destructor stub
}

void SortingSwitchService::sortingSwitchOpen() {
	hal_->setPin(PIN_4);
}

void SortingSwitchService::sortingSwitchClose() {
	hal_->clearPin(PIN_4);
}

