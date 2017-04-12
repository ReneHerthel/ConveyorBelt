/*
 * Copyright (C) 2017 Rene Herthel
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
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef CONVEYORBELT_H_
#define CONVEYORBELT_H_

#include "BConveyorBelt.h"

class ConveyorBeltHal : public BConveyorBelt {
public:
	/**
	 * @brief Switch to the next state of the ConveyorBeltState's.
	 *
	 * @param The next state the ConveyorBelt will go in.
	 */
	 void nextState(ConveyorBeltState state);
};

#endif /* CONVEYORBELT_H_ */
/** @} */
