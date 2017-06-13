/*
 * TestPuckManager.cpp
 *
 *  Created on: 12.06.2017
 *      Author: aca592
 */

#include "TestPuckManager.h"

#include <iostream>

SETUP(TestPuckManager) {
	REG_TEST(test1, 1, "Test the longest path with one puck only");
	REG_TEST(test2, 2, "Test the longest path with three pucks ");
	return 1;
}

BEFORE_TC(TestPuckManager) {
	return 1;
}

AFTER_TC(TestPuckManager) {
	return 1;
}

BEFORE(TestPuckManager) {
	manager = new PuckManager();
	return 1;
}

AFTER(TestPuckManager) {
	delete manager;
	return 1;
}

TEST_IMPL(TestPuckManager, test1) {
	for(uint32_t i = 0; i < sizeof(signalArrayLongestPath) / sizeof(PuckSignal::Signal); ++i) {
		PuckManager::ManagerReturn returnVal = manager->process(signalArrayLongestPath[i]);
		if(returnVal.speedSignal != returnArrayLongestPath[i].speedSignal) {
			std::cout << "[TEST 1] SpeedSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.actorFlag != returnArrayLongestPath[i].actorFlag && returnVal.actorSignal != returnArrayLongestPath[i].actorSignal) {
			std::cout << "[TEST 1] ActorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.errorFlag != returnArrayLongestPath[i].errorFlag && returnVal.errorSignal != returnArrayLongestPath[i].errorSignal) {
			std::cout << "[TEST 1] ErrorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.slideFullFlag != returnArrayLongestPath[i].slideFullFlag) {
			std::cout << "[TEST 1] SlideFlag differs!" << std::endl;
			return TEST_FAILED;
		}

		if(		(returnVal.puck != nullptr && returnArrayLongestPath[i].puck == nullptr) ||
				(returnVal.puck == nullptr && returnArrayLongestPath[i].puck != nullptr)) {
			std::cout << "[TEST 1] Puck pointer differs!" << std::endl;
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckManager, test2) {
	for(uint32_t i = 0; i < sizeof(signalArrayMultiplePucks) / sizeof(PuckSignal::Signal); ++i) {
		PuckManager::ManagerReturn returnVal = manager->process(signalArrayMultiplePucks[i]);
		if(returnVal.speedSignal != returnArrayMultiplePucks[i].speedSignal) {
			std::cout << "[TEST 2] SpeedSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if((returnVal.actorFlag != returnArrayMultiplePucks[i].actorFlag && returnVal.actorSignal != returnArrayMultiplePucks[i].actorSignal) || returnVal.actorFlag != returnArrayMultiplePucks[i].actorFlag) {
			std::cout << "[TEST 2] ActorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if((returnVal.errorFlag != returnArrayMultiplePucks[i].errorFlag && returnVal.errorSignal != returnArrayMultiplePucks[i].errorSignal) || returnVal.errorFlag != returnArrayMultiplePucks[i].errorFlag) {
			std::cout << "[TEST 2] ErrorSignal differs! Should be: " + std::to_string(returnArrayMultiplePucks[i].errorSignal) + " but was: " + std::to_string(returnVal.errorSignal) << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.slideFullFlag != returnArrayMultiplePucks[i].slideFullFlag) {
			std::cout << "[TEST 2] SlideFlag differs!" << std::endl;
			return TEST_FAILED;
		}

		if(		(returnVal.puck != nullptr && returnArrayMultiplePucks[i].puck == nullptr) ||
				(returnVal.puck == nullptr && returnArrayMultiplePucks[i].puck != nullptr)) {
			std::cout << "[TEST 2] Puck pointer differs!" << std::endl;
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}
