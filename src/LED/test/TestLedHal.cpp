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
 * @brief      test declaration of the LED component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestLedHal.h"
#include "LedService.h"
#include "Led.h"

#include <iostream>
#include <thread>
#include <chrono>

void TestLedHal::startTest() {


	// NOTE: Make sure your thread has permissions before using this!


	LedService service;

	std::cout<<"[TestLedHal] Start."<<std::endl;

	std::cout<<"[TestLedHal] Enable all led's in a period of half of a seconds each."<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOn(START);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOn(RESET);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOn(Q1);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOn(Q2);

	std::cout<<"[TestLedHal] Disables all led's in a period of half of a seconds each."<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOff(START);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOff(RESET);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOff(Q1);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service.ledOff(Q2);

	std::cout<<"[TestLedHal] Done."<<std::endl;
}
