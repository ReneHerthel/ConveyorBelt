/*!
 *    \file  TestPuckSort.h
 *   \brief  Declares the single tests
 *
 *   Test signals are defined to avoid dealing with PuckType structures.
 *
 *  \author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *  \internal
 *       Created:  06/14/2017
 * Last modified:  06/21/2017
 *     Copyright:  Copyright (c) 2017 Stephan Jänecke licensed under the
 *     MIT License
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

/*! \brief Define signal for binary 1 encoded puck */
#define TESTSIGNAL_BITCODE1 		{ signal_t { {SignalID::PATTERN_ID, 1, 0, 0} }, 0, 0, 0 } 
/*! \brief Define signal for binary 2 encoded puck */
#define TESTSIGNAL_BITCODE2 		{ signal_t { {SignalID::PATTERN_ID, 0, 1, 0} }, 0, 0, 0 }
/*! \brief Define signal for binary 4 encoded puck */
#define TESTSIGNAL_BITCODE4 		{ signal_t { {SignalID::PATTERN_ID, 0, 0, 1} }, 0, 0, 0 }
/*! \brief Define signal for binary 5 encoded puck */
#define TESTSIGNAL_BITCODE5 		{ signal_t { {SignalID::PATTERN_ID, 1, 0, 1} }, 0, 0, 0 }
/*! \brief Define signal for flipped puck */
#define TESTSIGNAL_FLIPPED  		{ signal_t { {SignalID::FLIPPED_ID, 0, 0, 0} }, 0, 0, 0 }
/*! \brief Define signal for puck with metal. Notice the set metal bit. */
#define TESTSIGNAL_HOLEWITHMETAL    { signal_t { { SignalID::NORMAL_ID, 1, 0, 0} }, 1, 0, 0 }
/*! \brief Define signal for invalid puck */
#define TESTSIGNAL_INVALID			{ signal_t { {SignalID::INVALID_ID, 0, 0, 0} }, 0, 0, 0 }
/*! \brief Define signal for normal puck without metal */
#define TESTSIGNAL_HOLEWITHOUTMETAL { signal_t { { SignalID::NORMAL_ID, 0, 0, 0} }, 0, 0, 0 }
/*! \brief Define signal for slide full message from local puck */
#define TESTSIGNAL_SLIDEFULL_OWN    PuckSignal::SLIDE_FULL
/*! \brief Define signal for slide full message from remote puck */
#define TESTSIGNAL_SLIDEFULL_OTHER  ser_proto_msg::SLIDE_FULL_SER

class TestPuckSort : public TestCase {
	public:
		TestPuckSort(int id, std::string brief)
		: TestCase(id, brief)
		, context(nullptr)
		{};
	protected:
        /*!
         *  \brief Take the shortest path to the end of the sequence.
         *
         *  \test Feed the following sequence
         *  -# holeWithoutMetal 
         *  -# holeWithoutMetal
         *  -# holeWithMetal
         */
		TEST(test1);
        /*!
         *  \brief Test trivial transitions from state Start
         *
         *  \test Beginning from Start feed all puck signals once ending
         *  with holeWithoutMetal. A state transition to
         *  GotHoleUpWoMetal should occur. The conditionals returned
         *  depend on the machine the test is run on.
         */
		TEST(test2);
        /*!
         *  \brief Test incoming slide full message from machine 1
         *
         *  \test On machine 1 pass all pucks once slide full has been
         *  received.
         *  On machine 2 discard all pucks.
         */
		TEST(test3);
        /*!
         *  \brief Test incoming slide full message from machine 2
         *
         *  \test On machine 1 discard all pucks once slide full has been
         *  received. Pass pucks in sequence.
         *  On machine 2 pass all pucks once slide full has been
         *  received.
         */
		TEST(test4);
		TEST_CASE_METHODS;
	private:
        PuckSortContext *context; /*!< \brief Save the pointer to the
                                    state machine context under test  */
};

#endif /* TESTPUCKSORT_H_ */
