/*
* Copyright (C) 2017 René Herthel
*
* This file is subject to the terms and conditions of the MIT License.
* See the file LICENSE in the top level directory for more details.
*/

/**
* @ingroup    height_measurement
* @{
*
* @brief      Header of the HeightMeasurement component
*
* @author     René Herthel <rene.herthel@haw-hamburg.de>
*/

#ifndef HEIGHTMEASUREMENT_H_
#define HEIGHTMEASUREMENT_H_

namespace HAL {
	class HeightMeasurement	{
		public:
			HeightMeasurement();

			HeightMeasurement(const int port, const int pin) : port_(port), pin_(pin)
			{
				// No need for assigment here.
			}

			~HeightMeasurement();

			/* TODO:
			 * Reads the analog value of the sensor.
			 * Maybe it is better to return the whole pattern..
			 */
			int ReadAnalog(int offset);

			/* TODO:
			 * @brief Reads the whole pattern-code of the working piece.
			 *      
			 * @return The code of the working peace?
			 */
			int ReadPattern(int offset);

		private:
			int port_;
			int pin_;
	};
}

#endif /* HEIGHTMEASUREMENT_H_ */
/** @} */
