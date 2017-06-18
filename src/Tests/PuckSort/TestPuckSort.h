/*!
 * @file TestPuckSort.h
 * @brief
 *
 * @author Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 * @internal
 * Created 06/14/2017 06:29:22 PM
 * Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef TESTPUCKSORT_H_
#define TESTPUCKSORT_H_

#include "TestCase.h"
#include "TestFramework.h"

#include "PuckSortContext.h"
#include "PuckSignal.h"
#include "Signals.h"
#include "HeightSignal.h"
#include "SerialProtocoll.h"

#define TESTSIGNAL_BITCODE1 		{ signal_t { {SignalID::PATTERN_ID, 1, 0, 0} }, 0, 0, 0 }
#define TESTSIGNAL_BITCODE2 		{ signal_t { {SignalID::PATTERN_ID, 0, 1, 0} }, 0, 0, 0 }
#define TESTSIGNAL_BITCODE4 		{ signal_t { {SignalID::PATTERN_ID, 0, 0, 1} }, 0, 0, 0 }
#define TESTSIGNAL_BITCODE5 		{ signal_t { {SignalID::PATTERN_ID, 1, 0, 1} }, 0, 0, 0 }
#define TESTSIGNAL_FLIPPED  		{ signal_t { {SignalID::FLIPPED_ID, 0, 0, 0} }, 0, 0, 0 }
#define TESTSIGNAL_HOLEWITHMETAL    { signal_t { { SignalID::NORMAL_ID, 1, 0, 0} }, 1, 0, 0 }
#define TESTSIGNAL_INVALID			{ signal_t { {SignalID::INVALID_ID, 0, 0, 0} }, 0, 0, 0 }
#define TESTSIGNAL_HOLEWITHOUTMETAL { signal_t { { SignalID::NORMAL_ID, 0, 0, 0} }, 0, 0, 0 }
#define TESTSIGNAL_SLIDEFULL_OWN    PuckSignal::SLIDE_FULL
#define TESTSIGNAL_SLIDEFULL_OTHER  ser_proto_msg::SLIDE_FULL_SER

class TestPuckSort : public TestCase {
	public:
		TestPuckSort(int id, std::string brief)
		: TestCase(id, brief)
		, context(nullptr)
		{};
	protected:
		TEST(test1);
		TEST(test2);
		TEST(test3);
		TEST(test4);
		TEST_CASE_METHODS;
	private:
		PuckSortContext *context;
};

#endif /* TESTPUCKSORT_H_ */
