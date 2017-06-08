/*
 * TestPuckStateMachine.h
 *
 *  Created on: 08.06.2017
 *      Author: aca592
 */

#ifndef TESTPUCKSTATEMACHINE_H_
#define TESTPUCKSTATEMACHINE_H_

#include "TestCase.h"
#include "TestFramework.h"

#include "PuckContext.h"
#include "PuckSignal.h"

class TestPuckStateMachine : public TestCase {
public:
	TestPuckStateMachine(int id, std::string brief) : TestCase(id, brief) { };
protected:
	TEST(test1);
private:
	PuckContext *context;
};

#endif /* TESTPUCKSTATEMACHINE_H_ */
