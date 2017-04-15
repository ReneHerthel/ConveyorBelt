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

#ifndef BCONVEYORBELT_H_
#define BCONVEYORBELT_H_

class BConveyorBelt {
public:
	/*
	 * @brief Virtual deconstructor.
	 */
	virtual ~BConveyorBelt();

	/*
	 * @brief Set the corresponding pin in the port.
	 */
	virtual void setMask(const int mask) = 0;
};


#endif /* BCONVEYORBELT_H_ */
/** @} */
