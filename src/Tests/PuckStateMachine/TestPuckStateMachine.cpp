/*
 * TestPuckStateMachine.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca592
 */

#include "TestPuckStateMachine.h"

SETUP(TestPuckStateMachine) {
	REG_TEST(test1, 1, "Test the longest path");
	return 1;
}

BEFORE_TC(TestPuckStateMachine) {
	uint32_t puckID = 1;
	context = new PuckContext(puckID);
	return 1;
}

AFTER_TC(TestPuckStateMachine) {
	delete context;
	return 1;
}

BEFORE(TestPuckStateMachine) {
	return 1;
}

AFTER(TestPuckStateMachine) {
	return 1;
}

TEST_IMPL(TestPuckStateMachine, test1) {
	PuckSignal::Signal signal;
	PuckSignal::Return returnVal;

	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT and returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.TimerSignal = PuckSignal::TimerSignal;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT and returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT and returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	return TEST_PASSED;
}
