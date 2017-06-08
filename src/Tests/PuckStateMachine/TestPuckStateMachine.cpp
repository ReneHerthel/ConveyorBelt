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
	context = new PuckContext();
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

	return TEST_PASSED;
}
