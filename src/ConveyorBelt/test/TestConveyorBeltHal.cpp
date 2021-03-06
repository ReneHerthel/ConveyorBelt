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
 * @brief      Test function declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestConveyorBeltHal.h"
#include "ConveyorBeltService.h"
#include "ConveyorBeltState.h"

#include <iostream>
#include <thread>
#include <chrono>

void TestConveyorBeltHal::startTest() {


	// NOTE: Make sure your thread has permissions before using this!


	ConveyorBeltService conveyorBelt;

	std::cout<<"[TestConveyorBeltHal] Start."<<std::endl;

	std::cout<<"[TestConveyorBeltHal] Run a configured routine."<<std::endl;

	conveyorBelt.changeState(RIGHTFAST);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(STOP);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(LEFTSLOW);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(RIGHTFAST);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(RIGHTSLOW);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(LEFTFAST);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 seconds.

	conveyorBelt.changeState(STOP);

	std::cout<<"[TestConveyorBeltHal] Test done."<<std::endl;
}

/** @} */
