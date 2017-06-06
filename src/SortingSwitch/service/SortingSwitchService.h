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
	/*
	 * @brief Default constructor.
	 */
	SortingSwitchService();

	/*
	 * @brief Virtual destructor.
	 */
	virtual ~SortingSwitchService();

	/*
	 * @brief Opens the sorting switch.
	 */
	void sortingSwitchOpen();

	/*
	 * @brief Close the sorting switch.
	 */
	void sortingSwitchClose();

private:
	/*
	 * @brief A reference to the hal object of this component.
	 */
	SortingSwitchHal* hal_;
};

#endif /* SORTINGSWITCHSERVICE_H_ */
