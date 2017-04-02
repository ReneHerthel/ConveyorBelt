/*
 * Copyright (C) 2017 René Herthel
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
 * @author     René Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef LED_H_
#define LED_H_

namespace HAL {
	class LED {
		public:
			LED();

			/**
			 * @brief Constructor with port and pin initialization.
			 *
			 * @param The port of the LED.
			 * @param The pin of the LED.
			 */
			LED(const int port, const int pin) : port_(port), pin_(pin)
			{
				// No need for assigment here.
			}

			~LED();

			/**
			 * @brief Turn the LED on.
			 */
			void On();

			/*
			 * @brief Turn the LED off.
			 */
			void Off();

		private:
			int port_;
			int pin_;
	};
}

#endif /* LED_H_ */
/** @} */
