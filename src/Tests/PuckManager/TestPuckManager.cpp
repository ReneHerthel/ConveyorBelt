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
			std::cout << "SpeedSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.actorFlag != returnArrayLongestPath[i].actorFlag && returnVal.actorSignal != returnArrayLongestPath[i].actorSignal) {
			std::cout << "ActorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.errorFlag != returnArrayLongestPath[i].errorFlag && returnVal.errorSignal != returnArrayLongestPath[i].errorSignal) {
			std::cout << "ErrorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if(returnVal.slideFullFlag != returnArrayLongestPath[i].slideFullFlag) {
			std::cout << "SlideFlag differs!" << std::endl;
			return TEST_FAILED;
		}

		if(		(returnVal.puck != nullptr && returnArrayLongestPath[i].puck == nullptr) ||
				(returnVal.puck == nullptr && returnArrayLongestPath[i].puck != nullptr)) {
			std::cout << "Puck pointer differs!" << std::endl;
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}
