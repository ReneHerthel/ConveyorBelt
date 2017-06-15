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

	holeWithMetal.ID = SignalID::NORMAL_ID;
	holeWithMetal.BIT0 = 0;
	holeWithMetal.BIT1 = 0;
	holeWithMetal.BIT2 = 0;

	holeWithoutMetal.ID = SignalID::NORMAL_ID;
	holeWithoutMetal.BIT0 = 0;
	holeWithoutMetal.BIT1 = 0;
	holeWithoutMetal.BIT2 = 0;

	signalArrayShortestPath[0]= { holeWithoutMetal, 0, 0, 0 };
	signalArrayShortestPath[1]= { holeWithoutMetal, 0, 0, 0 };
	signalArrayShortestPath[2]= {    holeWithMetal, 1, 0, 0 };

	return 1;
}

AFTER(TestPuckSort) {
	delete context;
	return 1;
}

TEST_IMPL(TestPuckSort, test1) {
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayShortestPath); ++arrayIterator ) {
		cout << "Type: " << signalArrayShortestPath[arrayIterator].heightType.ID << "Metal: " << signalArrayShortestPath[arrayIterator].metal << endl;

		bool returnVal = context->process(signalArrayShortestPath[arrayIterator]);
		if ( returnVal != returnArrayShortestPath[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

