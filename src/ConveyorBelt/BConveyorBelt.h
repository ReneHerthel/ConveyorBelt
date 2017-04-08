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
* @brief      Function declaration of the LED component
*
* @author     Rene Herthel <rene.herthel@haw-hamburg.de>
*/

#ifndef B_CONVEYOR_BELT_H_
#define B_CONVEYOR_BELT_H_

#include "ConveyorBeltState.h"

class BConveyorBelt {
public:
	virtual ~BConveyorBelt();
	virtual void nextState(ConveyorBeltState state) = 0;
};

#endif /* B_CONVEYOR_BELT_H_ */
/** @} */
