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

#ifndef BSORTINGSWITCH_H_
#define BSORTINGSWITCH_H_

class BSortingSwitch {
public:

	/*
	 * @brief The virtual destructor.
	 */
	virtual ~BSortingSwitch();

	/*
	 * @brief Set the corresponding pin in the register.
	 */
	virtual void setPin(const int pin) = 0;

	/*
	 * @brief Clear the corresponding pin in the register.
	 */
	virtual void clearPin(const int pin) = 0;
};

#endif /* BSORTINGSWITCH_H_ */
/** @} */
