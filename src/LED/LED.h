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
  * @brief      Header declaration of the LED component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef LED_H_
#define LED_H_

namespace HAL {
	class LED {
	public:
		/**
		 * @brief Constructor with port and pin initialization.
		 *
		 * @param The port of the LED.
		 * @param The pin of the LED.
		 */
		LED(const int port, const int pin);

		~LED();

		/**
		 * @brief Turn the LED on.
		 */
		void on();

		/*
		 * @brief Turn the LED off.
		 */
		void off();

	private:
		int port_;
		int pin_;
	};
}

#endif /* LED_H_ */
/** @} */
