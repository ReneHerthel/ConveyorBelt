/*
 * TestPortA.cpp
 *
 *  Created on: 15.06.2017
 *      Author: abo000
 */

#include "TestPortA.h"

#include "TestPulseMessageWrapper.h"

#include "IConveyorBelt.h"
#include "ConveyorBeltService.h"
#include "ISortingSwitch.h"
#include "SortingSwitchService.h"

#include <chrono>
#include <thread>

SETUP(TestPortA) {
    REG_TEST(test1, 1, "Test the function of the sorting switch and conveyor belt");
    return 1;
}

BEFORE_TC(TestPortA) {
    return 1;
}

AFTER_TC(TestPortA) {
	return 1;
}

BEFORE(TestPortA) {
    return 1;
}

AFTER(TestPortA) {
	return 1;
}

TEST_IMPL(TestPortA, test1) {

    ISortingSwitch * sortingSwitch = new SortingSwitchService();
    sortingSwitch->sortingSwitchOpen();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    sortingSwitch->sortingSwitchClose();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    sortingSwitch->sortingSwitchOpen();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    sortingSwitch->sortingSwitchClose();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    sortingSwitch->sortingSwitchOpen();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    sortingSwitch->sortingSwitchClose();

    IConveyorBelt * conveyorBelt = new ConveyorBeltService();
    conveyorBelt->changeState(ConveyorBeltState::RIGHTFAST);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    conveyorBelt->changeState(ConveyorBeltState::RIGHTSLOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    conveyorBelt->changeState(ConveyorBeltState::STOP);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    conveyorBelt->changeState(ConveyorBeltState::LEFTFAST);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    conveyorBelt->changeState(ConveyorBeltState::LEFTSLOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    conveyorBelt->changeState(ConveyorBeltState::STOP);

    return TEST_PASSED; // LOL
}


