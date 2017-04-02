/*
 * Copyright (C) 2017 René Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    sorting_switch
 * @{
 *
 * @brief      Header of the SortingSwitch component
 *
 * @author     René Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SORTINGSWITCH_H_
#define SORTINGSWITCH_H_

namespace HAL {
	class SortingSwitch	{
		public:
			SortingSwitch();

			/**
			 * @brief Constructor with port and pin initialization.
			 *
			 * @param The port of the SortingSwitch.
			 * @param The pin of the SortingSwitch.
			 */
			SortingSwitch(const int port, const int pin) : port_(port), pin_(pin) {
				// No need for assigment here.
			}

			~SortingSwitch();

			/**
			 * @brief Reads the currently input of the SortingSwitch.
			 *
			 * @return 0, when the SortingSwitch is open.
			 * @return 1, when the SortingSwitch is closed.
			 */
			int Read();

		private:
			int port_;
			int pin_;
	};
}

#endif /* SORTINGSWITCH_H_ */
/** @} */
