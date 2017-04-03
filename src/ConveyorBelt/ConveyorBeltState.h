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
  * @brief      Enums declaration of the ConveyorBelt component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef CONVEYORBELTSTATE_H_
#define CONVEYORBELTSTATE_H_

namespace HAL {
	enum ConveyorBeltState {
		RightFast,
		RightSlow,
		LeftFast,
		LeftSlow,
		Stopp,
	};
}

#endif /* CONVEYORBELTSTATE_H_ */
/** @} */
