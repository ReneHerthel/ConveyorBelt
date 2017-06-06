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
 * @brief      Interface declaration of the LED component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef ILED_H_
#define ILED_H_

#include "Led.h"

class ILed {
public:

	/*
	 * @brief Turns the led on
	 * @param The led which should be turned on
	 */
	virtual void ledOn(const Led led) = 0;

	/*
	 * @brief Turn the led off
	 * @param The led which should be turned off
	 */
	virtual void ledOff(const Led led) = 0;
};

#endif /* ILED_H_ */
/** @} */
