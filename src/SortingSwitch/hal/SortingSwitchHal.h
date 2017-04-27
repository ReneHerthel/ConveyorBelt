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
 * @brief      Header declaration of the SortingSwitch component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SORTINGSWITCHHAL_H_
#define SORTINGSWITCHHAL_H_

class SortingSwitchHal {
public:

	/*
	 * @brief Default constructor.
	 */
	SortingSwitchHal();

	/*
	 * @brief Set the corresponding pin into the register of the sorting switch.
	 */
	void set();

	/*
	 * @brief Set the corresponding pin into the register of the sorting switch.
	 */
	void clear();
};

#endif /* SORTINGSWITCHHAL_H_ */
/** @} */
