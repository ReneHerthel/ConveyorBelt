/*!
 *   \file TestPuckSort.cpp
 *   \brief  Tests the PuckSort state machine
 *
 *   See the test declarations for descriptions of the various tests.
 *   The test signals and expected conditionals are defined in every test.
 *
 *  \author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *  \internal
 *       Created:  06/14/2017
 * Last modified:  06/21/2017
 *     Copyright:  Copyright (c) 2017 Stephan Jänecke
 *
 *   This file is subject to the terms and conditions of the MIT
 *   License. See the file LICENSE in the top level directory for more
 *   details.
 */

#include "TestPuckSort.h"
#include <iostream>

using namespace std;
using namespace HeightMeasurement;
using namespace Serial_n;
using namespace PuckSignal;

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

    /*! \brief Define expected conditionals expected from state machine */
	bool expectedResults[3] {
		false,
		false,
		false,
	};

    /*! \brief Define signals to feed into state machine */
	/* TODO: Assign to every single data member of array index */
	PuckType testSignals[3] = {
			TESTSIGNAL_HOLEWITHOUTMETAL,
			TESTSIGNAL_HOLEWITHOUTMETAL,
			TESTSIGNAL_HOLEWITHMETAL
	};


    /* TODO: Refactor into function */
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(testSignals) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test2) {
    /*! \brief Define signals to feed into state machine */
	/* TODO: Assign to every single data member of array index */
	PuckType testSignals[8] = {
			TESTSIGNAL_BITCODE1,
			TESTSIGNAL_BITCODE2,
			TESTSIGNAL_BITCODE4,
			TESTSIGNAL_BITCODE5,
			TESTSIGNAL_FLIPPED,
			TESTSIGNAL_HOLEWITHMETAL,
			TESTSIGNAL_INVALID,
			TESTSIGNAL_HOLEWITHOUTMETAL,
	};

    /*! \brief Define expected conditionals expected from state machine
     * depending on machine */
    bool expectedResults[8] {
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
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(testSignals) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test3) {
    /*! \brief Define signals to feed into state machine */
	/* TODO: Assign to every single data member of array index */
	PuckType testSignals[8] = {
        TESTSIGNAL_HOLEWITHMETAL,
        TESTSIGNAL_BITCODE4,
        TESTSIGNAL_BITCODE4,
        TESTSIGNAL_INVALID,
        TESTSIGNAL_BITCODE5,
        TESTSIGNAL_INVALID,
        TESTSIGNAL_BITCODE5,
        TESTSIGNAL_INVALID,
	};

    /*! \brief Define expected conditionals expected from state machine
     * depending on machine */
    bool expectedResults[8] {
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
	for ( uint8_t arrayIterator = 0; arrayIterator < 4; ++arrayIterator ) {
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
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
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test4) {
	LOG_SCOPE;
    /*! \brief Define signals to feed into state machine */
	/* TODO: Assign to every single data member of array index */
	PuckType testSignals[8] = {
        TESTSIGNAL_HOLEWITHOUTMETAL,
        TESTSIGNAL_BITCODE1,
        TESTSIGNAL_BITCODE2,
        TESTSIGNAL_FLIPPED,
        TESTSIGNAL_BITCODE1,
        TESTSIGNAL_BITCODE2,
        TESTSIGNAL_FLIPPED,
        TESTSIGNAL_HOLEWITHOUTMETAL,
	};

    /*! \brief Define expected conditionals expected from state machine
     * depending on machine */
    bool expectedResults[8] {
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
	for ( uint8_t arrayIterator = 0; arrayIterator < 4; ++arrayIterator ) {
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
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
    LOG_DEBUG << "Continue" << endl;
	for ( uint8_t arrayIterator = 4; arrayIterator < 8; ++arrayIterator ) {
		bool returnVal = context->process(testSignals[arrayIterator]);
		if ( returnVal != expectedResults[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}
