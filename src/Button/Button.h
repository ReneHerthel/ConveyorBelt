/*
 * Copyright (C) 2017 Ren� Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    button
 * @{
 *
 * @brief      Header declaration of the button component
 *
 * @author     Ren� Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef BUTTON_H_
#define BUTTON_H_

namespace HAL {
	class Button {
		public:
			Button();

			/**
			 * @brief Constructor with port and pin initialization.
			 *
			 * @param The port of the LED.
			 * @param The pin of the LED.
			 */
			Button(const int port, const int pin) : port_(port), pin_(pin)
			{
				// No need for assigment here.
			}

			~Button();

			/**
             * @brief Read the current state of the Button.
			 *
			 * @return 0, if the button is not pressed.
			 * @return 1, if the button is pressed.
			 */
			int Read();

		private:
			int port_;
			int pin_;
	};
}

#endif /* BUTTON_H_ */
/** @} */
