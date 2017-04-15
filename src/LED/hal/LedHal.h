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
 * @brief      Header declaration of the LedHal component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef LEDHAL_H_
#define LEDHAL_H_

#include "BLed.h"

class LedHal : public BLed{
public:

	/*
	 * @brief Constructor with port and pin initialization.
	 */
	LedHal(const int port, const int pin);

	void set();
	void clear();
private:
	int port_;
	int pin_;
};

#endif /* LEDHAL_H_ */
