/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    sorting_switch
 * @{
 *
 * @brief      Test function of the SortingSwitch component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestSortingSwitch.h"
#include "SortingSwitchService.h"

#include <iostream>
#include <thread>
#include <chrono>

void TestSortingSwitch::startTest() {


	// MAKE SURE YOUR THREAD HAS I/O PERMISSIONS!


	std::cout<<"[TestSortingSwitch] Start"<<std::endl;
	SortingSwitchService service;

	service.sortingSwitchOpen();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.sortingSwitchClose();


	std::this_thread::sleep_for(std::chrono::milliseconds(500));


	service.sortingSwitchOpen();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.sortingSwitchClose();


	std::this_thread::sleep_for(std::chrono::milliseconds(500));


	service.sortingSwitchOpen();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.sortingSwitchClose();

	std::cout<<"[TestSortingSwitch] Test done."<<std::endl;
}

/** @} */
