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
		TEST_CASE_METHODS;
	private:
		PuckSortContext *context;


		// holeWithoutMetal > holeWithoutMetal > holeWithMetal
		// TODO: Makeup sane signal initialization
		PuckType signalArrayShortestPath[3];

		HeightMeasurement::signal_t holeWithoutMetal;
		HeightMeasurement::signal_t holeWithMetal;

		bool returnArrayShortestPath[3] {
			false,
			false,
			false,
		};
};

#endif /* TESTPUCKSORT_H_ */
