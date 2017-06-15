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
 * @brief      Hal header declaration of the Led component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef LEDHAL_H_
#define LEDHAL_H_

class LedHal {
public:

	/*
	 * @brief Constructor with port and pin initialization.
	 * @param [port] The corresponding port of the led.
	 * @param [pin] The corresponding pin of the led.
	 */
	LedHal(const int port, const int pin);

	/*
	 * @brief Enables the corresponding led.
	 */
	void set();

	/*
	 * @brief Disables the corresponding led.
	 */
	void clear();

private:
	int port_;
	int pin_;
};

#endif /* LEDHAL_H_ */
