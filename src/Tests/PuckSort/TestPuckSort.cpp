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
	return 1;
}

AFTER(TestPuckSort) {
	delete context;
	return 1;
}

TEST_IMPL(TestPuckSort, test1) {
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayShortestPath); ++arrayIterator ) {
		printf("Type: %d Metal: %d", signalArrayShortestPath[arrayIterator].heightType.ID, signalArrayShortestPath[arrayIterator].metal);

		bool returnVal = context->process(signalArrayShortestPath[arrayIterator]);
		if ( returnVal != returnArrayShortestPath[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

