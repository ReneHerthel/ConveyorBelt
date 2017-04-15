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

#ifndef BLED_H_
#define BLED_H_

class BLed {
public:

	/*
	 * @brief default virtual constructor of the BLed interface.
	 */
	virtual ~BLed();

	/*
	 * @brief Enables the corresponding led.
	 */
	virtual void set() = 0;

	/*
	 * @brief Disables the corresponding led.
	 */
	virtual void clear() = 0;
};

#endif /* BLED_H_ */
/** @} */
