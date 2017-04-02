/*
 * Copyright (C) 2017 René Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    conveyor_belt
 * @{
 *
 * @brief      Header of the ConveyorBelt component
 *
 * @author     René Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef CONVEYORBELT_H_
#define CONVEYORBELT_H_

#include "ConveyorBeltState.h"

namespace HAL {
	class ConveyorBelt {
	    public:
		    ConveyorBelt();

			/**
			 * @brief Constructor with port and pin initialization.
			 *
			 * @param The port of the ConveyorBelt.
			 * @param The pin of the ConveyorBelt.
			 */
			ConveyorBelt(const int port, const int pin) : port_(port), pin_(pin) { 
				// No need for assigment here.
			}

		    ~ConveyorBelt();

			/** 
			 * @brief Switch to the next state of the ConveyorBeltState's.
			 * 
			 * @param The next state the ConveyorBelt will go in.
			 */
			void NextState(ConveyorBeltState state);

		private:
			int port_;
			int pin_;
	};
}

#endif /* CONVEYORBELT_H_ */
/** @} */
