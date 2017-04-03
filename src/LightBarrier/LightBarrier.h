/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    light_barrier
  * @{
  *
  * @brief      Header of the LightBarrier component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef LIGHTBARRIER_H_
#define LIGHTBARRIER_H_

namespace HAL {
	class LightBarrier {
	public:
		/**
		 * @brief Constructor with port and pin initialization.
		 *
		 * @param The port of the LightBarrier.
		 * @param The pin of the LightBarrier.
		 */
		LightBarrier(const int port, const int pin);

		~LightBarrier();

		/**
		 * @brief Reads the currently input of the LightBarrier.
		 *
		 * @return 0, when the LightBarrier is open.
		 * @return 1, when the LightBarrier is closed.
		 */
		int read();

	private:
		int port_;
		int pin_;
	};
}

#endif /* LIGHTBARRIER_H_ */
/** @} */
