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
#ifndef CONVEYORBELTHAL_H_
#define CONVEYORBELTHAL_H_

#include "BConveyorBelt.h"

class ConveyorBeltHal : public BConveyorBelt {
public:

	/*
	 * @brief Default constructor.
	 */
	ConveyorBeltHal(const int port);

	/*
	 * @brief Default deconstructor.
	 */
	~ConveyorBeltHal();

	void setMask(const int mask);
private:
	int port_;
};

#endif /* CONVEYORBELTHAL_H_ */

/** @} */
