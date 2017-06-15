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

class TestPuckSort : public TestCase {
	public:
		TestPuckSort(int id, std::string brief)
		: TestCase(id, brief)
		, context(nullptr)
		{};
	protected:
		TEST(test1);
		TEST(test2);
		TEST_CASE_METHODS;
	private:
		PuckSortContext *context;


		// holeWithoutMetal > holeWithoutMetal > holeWithMetal
		// TODO: Makeup sane signal initialization
		PuckType signalArrayShortestPath[3];

		bool returnArrayShortestPath[3] {
			false,
			false,
			false,
		};

		PuckType signalArrayAllSignals[8];

		// Beginning from Start try all transitions
        bool returnArrayAllSignalsStart[8] {
        			true,
        			true,
        			true,
        			true,
        			true,
        			true,
        			true,
        			false, // Changing into state GotHoleUpWoMetal
        };

};

#endif /* TESTPUCKSORT_H_ */
