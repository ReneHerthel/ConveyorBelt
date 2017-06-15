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
  * @brief      Service header declaration of the LED component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef LEDSERVICE_H_
#define LEDSERVICE_H_

#include "ILed.h"
#include "LedHal.h"

#include <vector>

class LedService : public ILed {
public:

	/*
	 * @brief Default constructor.
	 */
	LedService();

	/*
	 * @brief Turns a predefined led on.
	 * @param [led] The led which should be turned on.
	 */
	void ledOn(const Led led);

	/*
	 * @brief Turns a predefined led off.
	 * @param [led] The led which should be turned off.
	 */
	void ledOff(const Led led);

private:

	/*
	 * @brief A list with all led's.
	 */
	std::vector<LedHal*> m_leds;
};

#endif /* LEDSERVICE_H_ */
/** @} */
