/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    metal_detector
  * @{
  *
  * @brief      Header of the MetalDetector component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef METALDETECTOR_H_
#define METALDETECTOR_H_

namespace HAL {
	class MetalDetector {
	public:
		/**
		 * @brief Constructor with port and pin initialization.
		 *
		 * @param The port of the MetalDetector.
		 * @param The pin of the MetalDetector.
		 */
		MetalDetector(const int port, const int pin);

		~MetalDetector();

		/**
		 * @brief Reads the currently input of the MetalDetector.
		 *
		 * @return 0, when the MetalDetector is open.
		 * @return 1, when the MetalDetector is closed.
		 */
		int read();

	private:
		int port_;
		int pin_;
	};
}

#endif /* METALDETECTOR_H_ */
/** @} */
