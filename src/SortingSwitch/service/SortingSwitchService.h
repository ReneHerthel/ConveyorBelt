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

#ifndef SORTINGSWITCHSERVICE_H_
#define SORTINGSWITCHSERVICE_H_

#include "ISortingSwitch.h"
#include "SortingSwitchHal.h"

class SortingSwitchService : public ISortingSwitch {
public:
	SortingSwitchService();
	virtual ~SortingSwitchService();

	/*
	 * @brief
	 */
	void sortingSwitchOpen();

	/*
	 * @brief
	 */
	void sortingSwitchClose();

private:
	SortingSwitchHal* hal_;
};

#endif /* SORTINGSWITCHSERVICE_H_ */
