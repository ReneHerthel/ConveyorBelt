/*
* Copyright (C) 2017 Rene Herthel
*
* This file is subject to the terms and conditions of the MIT License.
* See the file LICENSE in the top level directory for more details.
*/

/**
 * @ingroup    led
 * @{
 *
 * @brief      Function declaration of the LED component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef B_SORTING_SWITCH_H_
#define B_SORTING_SWITCH_H_

class BSortingSwitch {
public:
	virtual ~BSortingSwitch();

	/*
	 * @brief Opens the sorting switch by setting the corresponding bit.
	 */
	virtual void open() = 0;

	/*
	 * @brief Close the sorting switch by setting the corresponding bit.
	 */
	virtual void close() = 0;
};

#endif /* B_SORTING_SWITCH_H_ */
