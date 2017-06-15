/*!
 * @file TestPuckSort.cpp
 * @brief
 *
 * @author Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 * @internal
 * Created 06/14/2017 06:28:22 PM
 * Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#include "TestPuckSort.h"

using namespace std;

SETUP(TestPuckSort) {
	REG_TEST(test1, 1, "Test shortest path");
	REG_TEST(test2, 2, "Test all transitions in Start");
	REG_TEST(test3, 3, "Test SLIDE_FULL signals");
	return 1;
}

BEFORE_TC(TestPuckSort) {
	return 1;
}

AFTER_TC(TestPuckSort) {
	return 1;
}

BEFORE(TestPuckSort) {
	context = new PuckSortContext();

	return 1;
}

AFTER(TestPuckSort) {
	delete context;
	return 1;
}

TEST_IMPL(TestPuckSort, test1) {
	// holeWithoutMetal > holeWithoutMetal > holeWithMetal
	bool returnArrayShortestPath[3] {
		false,
		false,
		false,
	};

	PuckType signalArrayShortestPath[3] = {
			TESTSIGNAL_HOLEWITHOUTMETAL,
			TESTSIGNAL_HOLEWITHOUTMETAL,
			TESTSIGNAL_HOLEWITHMETAL,
	};


	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayShortestPath) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(signalArrayShortestPath[arrayIterator]);

		if ( returnVal != returnArrayShortestPath[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test2) {
	PuckType signalArrayAllSignals[8] = {
			TESTSIGNAL_BITCODE1,
			TESTSIGNAL_BITCODE2,
			TESTSIGNAL_BITCODE4,
			TESTSIGNAL_BITCODE5,
			TESTSIGNAL_FLIPPED,
			TESTSIGNAL_HOLEWITHMETAL,
			TESTSIGNAL_INVALID,
			TESTSIGNAL_HOLEWITHOUTMETAL,
	};

	// Beginning from Start try all transitions
    bool returnArrayAllSignalsStart[8] {
#if !MACHINE
    	// Machine 1 from Start
		false,  // Pass bitCode1
		true,   // Kill bitCode2
		true,   // Kill bitCode4
		false,  // Pass bitCode5
		true,   // Kill flipped
		true,   // Kill holeWithMetal
		false,  // Pass invalid
		false,  // Pass holeWithoutMetal and change into state GotHoleUpWoMetal
#else
    	// Machine 2 from Start
		true,  // Kill bitCode1
		true,  // Kill bitCode2
		true,  // Kill bitCode4
		true,  // Kill bitCode5
		true,  // Kill flipped
		true,  // Kill holeWithMetal
		true,  // Kill invalid
		false, // Pass holeWithoutMetal change into state GotHoleUpWoMetal
#endif
    };

	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayAllSignals) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test3) {
	// TODO: Test SLIDE_FULL signals
	return TEST_FAILED;
}
