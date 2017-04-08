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

class BLED {
public:
	virtual ~BLED();

	/**
	 * @brief Turn the LED on by setting the corresponding bit in the register.
	 */
	virtual void on() = 0;

	/*
	 * @brief Turn the LED off by deleting the corresponding bit int the register.
	 */
	virtual void off() = 0;

	/*
	 * @brief Reads the corresponding bit of the LED out of the registry and returns it.
	 */
	virtual int read() = 0;
};

#endif /* BLED_H_ */
/** @} */
