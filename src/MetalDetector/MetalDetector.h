/*
 * Copyright (C) 2017 René Herthel
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
 * @author     René Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef METALDETECTOR_H_
#define METALDETECTOR_H_

namespace HAL {
	class MetalDetector {
		public:
			MetalDetector();

			MetalDetector(const int port, const int pin) : port_(port), pin_(pin)
			{
				// No need for assigment here.
			}

			~MetalDetector();

			/**
			* @brief Reads the currently input of the MetalDetector.
			*
			* @return 0, when the MetalDetector is open.
			* @return 1, when the MetalDetector is closed.
			*/
			int Read();

		private:
			int port_;
			int pin_;
	};
}

#endif /* METALDETECTOR_H_ */
/** @} */
