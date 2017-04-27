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
 * @brief      Service Header declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef CONVEYORBELTSERVICE_H_
#define CONVEYORBELTSERVICE_H_

#include "IConveyorBelt.h"
#include "ConveyorBeltHal.h"

class ConveyorBeltService : public IConveyorBelt {
public:

	/*
	 * @brief Default constructor.
	 */
	ConveyorBeltService();

	/*
	 * @brief Default destructor.
	 */
	~ConveyorBeltService();

	/*
	 * @brief Changes the state of the conveyor belt by using the ConveyorBeltStates.
	 * @param The next state of the ConveyorBelt component.
	 */
	void ConveyorBeltChangeState(const ConveyorBeltState state);

private:
	ConveyorBeltHal* hal_;
};

#endif /* CONVEYORBELTSERVICE_H_ */
/** @} */
