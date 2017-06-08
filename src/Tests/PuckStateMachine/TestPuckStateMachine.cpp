/*
 * TestPuckStateMachine.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca592
 */

#include "TestPuckStateMachine.h"

SETUP(TestPuckStateMachine) {
	REG_TEST(test1, 1, "Test the longest path");
	REG_TEST(test2, 2, "Test error on every state of longest path");
	REG_TEST(test3, 3, "Test the slide path");
	return 1;
}

BEFORE_TC(TestPuckStateMachine) {
	return 1;
}

AFTER_TC(TestPuckStateMachine) {
	return 1;
}

BEFORE(TestPuckStateMachine) {
	uint16_t puckID = 1;
	context = new PuckContext(puckID);
	return 1;
}

AFTER(TestPuckStateMachine) {
	delete context;
	return 1;
}

TEST_IMPL(TestPuckStateMachine, test1) {
	for(uint32_t i = 0; i < sizeof(signalArrayLongestPath) / sizeof(PuckSignal::Signal); ++i) {
		PuckSignal::Return returnVal = context->process(signalArrayLongestPath[i]);
		if(		returnVal.puckReturn != returnArrayLongestPath[i].puckReturn ||
				returnVal.puckSpeed != returnArrayLongestPath[i].puckSpeed) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckStateMachine, test2) {
	PuckSignal::Signal errorSignal = {PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::LATE_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER};

	for(uint32_t i = 0; i < sizeof(signalArrayLongestPath) / sizeof(PuckSignal::Signal); ++i) {
		PuckSignal::Return returnVal;
		for(uint32_t j = 0; j < i; ++j) {
			returnVal = context->process(signalArrayLongestPath[j]);
			if(		returnVal.puckReturn != returnArrayLongestPath[j].puckReturn ||
					returnVal.puckSpeed != returnArrayLongestPath[j].puckSpeed) {
				return TEST_FAILED;
			}
		}

		returnVal = context->process(errorSignal);
		if(		returnVal.puckReturn != PuckSignal::PuckReturn::ERROR ||
				returnVal.puckSpeed != PuckSignal::PuckSpeed::STOP) {
			return TEST_FAILED;
		}

		uint16_t ID = context->getPuckID();
		delete context;
		context = new PuckContext(ID);
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckStateMachine, test3) {
	PuckSignal::Return returnVal;
	for(uint32_t j = 0; j < 2; ++j) {
		uint32_t i;
		for(i = 0; i < (sizeof(signalArraySlidePath) / sizeof(PuckSignal::Signal)) - 2; ++i) {
			returnVal = context->process(signalArraySlidePath[i]);
			if(		returnVal.puckReturn != returnArraySlidePath[i].puckReturn ||
					returnVal.puckSpeed != returnArraySlidePath[i].puckSpeed) {
				return TEST_FAILED;
			}
		}
		returnVal = context->process(signalArraySlidePath[i + j]);
		if(		returnVal.puckReturn != returnArraySlidePath[i + j].puckReturn ||
				returnVal.puckSpeed != returnArraySlidePath[i + j].puckSpeed) {
			return TEST_FAILED;
		}

		uint16_t ID = context->getPuckID();
		delete context;
		context = new PuckContext(ID);
	}
	return TEST_PASSED;
}

