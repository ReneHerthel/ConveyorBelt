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
 * @brief      Interface declaration of the SortingSwitch component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef ISORTINGSWITCH_H_
#define ISORTINGSWITCH_H_

class ISortingSwitch {
public:

	/*
	 * @brief Open the SortingSwitch.
	 */
	virtual void sortingSwitchOpen() = 0;

	/*
	 * @brief Close the SortingSwitch.
	 */
	virtual void sortingSwitchClose() = 0;
};

#endif /* ISORTINGSWITCH_H_ */
/** @} */
