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
	REG_TEST(test3, 3, "Test SLIDE_FULL reported by machine 1");
	REG_TEST(test4, 4, "Test SLIDE_FULL reported by machine 2");
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


    /* TODO: Refactor into function */
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
		true,   // Kill bitCode1
		false,  // Pass bitCode2
		false,  // Pass bitCode4
		true,   // Kill bitCode5
		true,   // Kill flipped
		false,  // Pass holeWithMetal
		true,   // Kill invalid
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

    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayAllSignals) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test3) {
	PuckType testSignalArray[8] = {
        TESTSIGNAL_HOLEWITHMETAL,
        TESTSIGNAL_BITCODE4,
        TESTSIGNAL_BITCODE4,
        TESTSIGNAL_INVALID,
        TESTSIGNAL_BITCODE5,
        TESTSIGNAL_INVALID,
        TESTSIGNAL_BITCODE5,
        TESTSIGNAL_INVALID,
	};

    bool returnArray[8] {
#if !MACHINE
    	// Machine 1 from Start
        false,
        true,
        true,
        true,
        // slide 1 is full
        false,
        false,
        false,
        false,
#else
    	// Machine 2 from Start
        true,
        true,
        true,
        true,
        // slide 1 is full
        true,
        true,
        true,
        true,
#endif
    };
    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 0; arrayIterator < 3; ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}

    /* Incoming slide full signal */
#if !MACHINE
    /* Slide 1 is full seen on machine 1 */
    context->process(TESTSIGNAL_SLIDEFULL_OWN);
#else
    /* Slide 1 is full seen on machine 2 */
    context->process(TESTSIGNAL_SLIDEFULL_OTHER);
#endif

    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 4; arrayIterator < 8; ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test4) {
	PuckType testSignalArray[8] = {
        TESTSIGNAL_HOLEWITHOUTMETAL,
        TESTSIGNAL_BITCODE1,
        TESTSIGNAL_BITCODE2,
        TESTSIGNAL_FLIPPED,
        TESTSIGNAL_BITCODE1,
        TESTSIGNAL_BITCODE2,
        TESTSIGNAL_FLIPPED,
        TESTSIGNAL_HOLEWITHOUTMETAL,
	};

    bool returnArray[8] {
#if !MACHINE
    	// Machine 1 from Start
        false,
        true,
        true,
        true,
        // slide 2 is full
        true,
        true,
        true,
        false,
#else
    	// Machine 2 from Start
        false,
        true,
        true,
        true,
        // slide 2 is full
        false,
        false,
        false,
        false,
#endif
    };
    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 0; arrayIterator < 3; ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}

    /* Incoming slide full signal */
#if !MACHINE
    /* Slide 2 is full seen on machine 1 */
    context->process(TESTSIGNAL_SLIDEFULL_OTHER);
#else
    /* Slide 2 is full seen on machine 2 */
    context->process(TESTSIGNAL_SLIDEFULL_OWN);
#endif

    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 4; arrayIterator < 8; ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);
		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}
