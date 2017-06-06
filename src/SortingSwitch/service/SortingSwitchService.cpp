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

#include <sys/neutrino.h>
#include <iostream>

SortingSwitchService::SortingSwitchService()
	:	hal_(new SortingSwitchHal())
{
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1)
	{
		std::cout << "[SortingSwitchService] Can't get hardware access." << std::endl;
	}
}

SortingSwitchService::~SortingSwitchService() {
	// TODO Auto-generated destructor stub
}

void SortingSwitchService::sortingSwitchOpen() {
	hal_->set();
}

void SortingSwitchService::sortingSwitchClose() {
	hal_->clear();
}

