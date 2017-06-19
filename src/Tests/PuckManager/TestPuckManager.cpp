/*
 * TestPuckManager.cpp
 *
 *  Created on: 12.06.2017
 *      Author: aca592
 */

#include "TestPuckManager.h"

#include <iostream>
#include "Logger.h"
#include "LogScope.h"

SETUP(TestPuckManager) {
	REG_TEST(test1, 1, "Test the longest path with one puck only");
	REG_TEST(test2, 2, "Test the longest path with three pucks");
	REG_TEST(test3, 3, "Test the longest path with late timer error with one puck only");
	REG_TEST(test4, 4, "Test the Warning to Error handle");
	return 1;
}

BEFORE_TC(TestPuckManager) {

	chid = timerReceiver.newChannel();

	//INIT CALIBRATION AND CALIBRATE
	Calibration& calibration = Calibration::getInstance();
	std::cout << "start Hightcal" << "\n";
	cout.flush();
	calibration.calibrateHeighMeasurement();
	std::cout << "start distancecal" << "\n";
		cout.flush();
	calibration.calibrate();
	return 1;
}

AFTER_TC(TestPuckManager) {
	return 1;
}

BEFORE(TestPuckManager) {
	manager = new PuckManager(chid);

	return 1;
}

AFTER(TestPuckManager) {
	delete manager;
	return 1;
}

TEST_IMPL(TestPuckManager, test1) {
	LOG_SCOPE;
	LOG_DEBUG << "-------------------TEST 1 ------------------\n";
	for(uint32_t i = 0; i < sizeof(signalArrayLongestPath) / sizeof(PuckSignal::Signal); ++i) {
		PuckManager::ManagerReturn returnVal = manager->process(signalArrayLongestPath[i]);
		if(returnVal.speedSignal != returnArrayLongestPath[i].speedSignal) {
			std::cout << "[TEST 1] SpeedSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if((returnVal.actorFlag != returnArrayLongestPath[i].actorFlag && returnVal.actorSignal != returnArrayLongestPath[i].actorSignal) || returnVal.actorFlag != returnArrayLongestPath[i].actorFlag) {
			std::cout << "[TEST 1] ActorSignal differs!" << std::endl;
			return TEST_FAILED;
		}

		if((returnVal.errorFlag != returnArrayLongestPath[i].errorFlag && returnVal.errorSignal != returnArrayLongestPath[i].errorSignal) || returnVal.errorFlag != returnArrayLongestPath[i].errorFlag) {
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
	LOG_SCOPE;
	LOG_DEBUG << "-------------------TEST 2 ------------------\n";
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

TEST_IMPL(TestPuckManager, test3) {
	LOG_SCOPE;
	LOG_DEBUG << "-------------------TEST 3 ------------------\n";
	PuckSignal::Signal errorSignal = {PuckSignal::SignalType::TIMER_SIGNAL, {{0}}, { .TimerInfo = { .puckID = 0, .type = PuckSignal::TimerType::LATE_TIMER } }, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER};

	for(uint32_t i = 1; i < (sizeof(signalArrayLongestPath) / sizeof(PuckSignal::Signal)); i++) {
		PuckManager::ManagerReturn returnVal;
		for(uint32_t j = 0; j < i; ++j) {
			returnVal = manager->process(signalArrayLongestPath[j]);
			if(returnVal.speedSignal != returnArrayLongestPath[j].speedSignal) {
				std::cout << "[TEST 3] SpeedSignal differs!" << std::endl;
				return TEST_FAILED;
			}

			if((returnVal.actorFlag != returnArrayLongestPath[j].actorFlag && returnVal.actorSignal != returnArrayLongestPath[j].actorSignal) || returnVal.actorFlag != returnArrayLongestPath[j].actorFlag) {
				std::cout << "[TEST 3] ActorSignal differs!" << std::endl;
				return TEST_FAILED;
			}

			if((returnVal.errorFlag != returnArrayLongestPath[j].errorFlag && returnVal.errorSignal != returnArrayLongestPath[j].errorSignal) || returnVal.errorFlag != returnArrayLongestPath[j].errorFlag) {
				std::cout << "[TEST 3] ErrorSignal differs!" << std::endl;
				return TEST_FAILED;
			}

			if(returnVal.slideFullFlag != returnArrayLongestPath[j].slideFullFlag) {
				std::cout << "[TEST 3] SlideFlag differs!" << std::endl;
				return TEST_FAILED;
			}

			if(		(returnVal.puck != nullptr && returnArrayLongestPath[j].puck == nullptr) ||
					(returnVal.puck == nullptr && returnArrayLongestPath[j].puck != nullptr)) {
				std::cout << "[TEST 3] Puck pointer differs!" << std::endl;
				return TEST_FAILED;
			}
		}

		// check error
		returnVal = manager->process(errorSignal);
		if(returnVal.errorFlag == false || returnVal.errorSignal != PuckManager::ErrorSignal::PUCK_LOST) {
			return TEST_FAILED;
		}

		delete manager;
		manager = new PuckManager(chid);
	}
	return TEST_PASSED;
}
TEST_IMPL(TestPuckManager, test4) {
	LOG_SCOPE;
	LOG_DEBUG << "-------------------TEST 4 ------------------\n";
	for(uint32_t i = 0; i < sizeof(signalArrayWarningToError) / sizeof(PuckSignal::Signal); ++i) {
			PuckManager::ManagerReturn returnVal = manager->process(signalArrayWarningToError[i]);
			if(returnVal.speedSignal != returnArrayWarningToError[i].speedSignal) {
				std::cout << "[TEST 4] SpeedSignal differs!" << std::endl;
				return TEST_FAILED;
			}

			if((returnVal.actorFlag != returnArrayWarningToError[i].actorFlag && returnVal.actorSignal != returnArrayWarningToError[i].actorSignal) || returnVal.actorFlag != returnArrayWarningToError[i].actorFlag) {
				std::cout << "[TEST 4] ActorSignal differs!" << std::endl;
				return TEST_FAILED;
			}

			if((returnVal.errorFlag != returnArrayWarningToError[i].errorFlag && returnVal.errorSignal != returnArrayWarningToError[i].errorSignal) || returnVal.errorFlag != returnArrayWarningToError[i].errorFlag) {
				std::cout << "[TEST 4] ErrorSignal differs! Should be: " + std::to_string(returnArrayWarningToError[i].errorSignal) + " but was: " + std::to_string(returnVal.errorSignal) << std::endl;
				return TEST_FAILED;
			}

			if(returnVal.slideFullFlag != returnArrayWarningToError[i].slideFullFlag) {
				std::cout << "[TEST 4] SlideFlag differs!" << std::endl;
				return TEST_FAILED;
			}

			if(		(returnVal.puck != nullptr && returnArrayWarningToError[i].puck == nullptr) ||
					(returnVal.puck == nullptr && returnArrayWarningToError[i].puck != nullptr)) {
				std::cout << "[TEST 4] Puck pointer differs!" << std::endl;
				return TEST_FAILED;
			}
		}
		return TEST_PASSED;
}
