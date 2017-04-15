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
  * @brief      Service declaration of the LED component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef LEDSERVICE_H_
#define LEDSERVICE_H_

#include "ILed.h"
#include "LedHal.h"

#include <iostream>
#include <vector>

class LedService : ILed {
public:
	LedService();
	void ledOn(const Led led);
	void ledOff(const Led led);

private:

	/*
	 * @brief A list with all led's.
	 */
	std::vector<LedHal*> halObjects_;
};

#endif /* LEDSERVICE_H_ */
/** @} */
