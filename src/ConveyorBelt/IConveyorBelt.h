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
 * @brief      Function declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef ICONVEYORBELT_H_
#define ICONVEYORBELT_H_

#include "ConveyorBeltState.h"

class IConveyorBelt {
public:

	/*
	 * @brief Virtual destructor.
	 */
	virtual ~IConveyorBelt();

	/*
	 * @brief Changes the state of the conveyor belt by using the ConveyorBeltStates.
	 */
	virtual void ConveyorBeltChangeState(const ConveyorBeltState state) = 0;
};

#endif /* ICONVEYORBELT_H_ */
/** @} */
