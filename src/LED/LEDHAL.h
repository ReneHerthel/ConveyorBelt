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

#include "BLED.h"

class LEDHAL : public BLED {
public:
	/**
	* @brief Constructor with port and pin initialization.
	*
	* @param The port of the LED.
	* @param The pin of the LED.
	*/
	LEDHAL(const int port, const int pin);

	~LEDHAL();

	/**
	* @brief Turn the LED on by setting the corresponding bit in the register.
	*/
	void on();

	/*
	* @brief Turn the LED off by deleting the corresponding bit int the register.
	*/
	void off();

private:
	int port_;
	int pin_;
};

#endif /* LED_H_ */
/** @} */
