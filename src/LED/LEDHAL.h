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
* @brief      Header declaration of the LEDHAL component
*
* @author     Rene Herthel <rene.herthel@haw-hamburg.de>
*/

#ifndef LEDHAL_H_
#define LEDHAL_H_

#include"BLED.h"

class LEDHal : public BLED {
public:
	/*
	 * @brief Creates a new LEDHal object with a port-pin (see HWadresses.h).
	 */
	LEDHal(const int ledPinMask);
	virtual ~LEDHal();
	void on();
	void off();
	int read();
private:
	int ledPinMask_;
};

#endif /* LED_H_ */
/** @} */
