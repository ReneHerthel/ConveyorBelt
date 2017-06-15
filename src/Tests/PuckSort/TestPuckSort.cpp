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
	std::cout << "__FUNCTION__: Passed All Test" << std::endl;
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

	// TODO: Kill the anonymous struct in signal_t
	signal_t bitCode1;
	signal_t bitCode2;
	signal_t bitCode4;
	signal_t bitCode5;
	signal_t flipped;
	signal_t holeWithoutMetal;
	signal_t holeWithMetal;
	signal_t invalid;

	bitCode1.ID = SignalID::NORMAL_ID;
	bitCode1.BIT0 = 1;
	bitCode1.BIT1 = 0;
	bitCode1.BIT2 = 0;

	bitCode2.ID = SignalID::NORMAL_ID;
	bitCode2.BIT0 = 0;
	bitCode2.BIT1 = 1;
	bitCode2.BIT2 = 0;

	bitCode4.ID = SignalID::NORMAL_ID;
	bitCode4.BIT0 = 0;
	bitCode4.BIT1 = 0;
	bitCode4.BIT2 = 1;

	bitCode5.ID = SignalID::NORMAL_ID;
	bitCode5.BIT0 = 1;
	bitCode5.BIT1 = 0;
	bitCode5.BIT2 = 1;

	flipped.ID = SignalID::FLIPPED_ID;
	flipped.BIT0 = 0;
	flipped.BIT1 = 0;
	flipped.BIT2 = 0;

	holeWithoutMetal.ID = SignalID::NORMAL_ID;
	holeWithoutMetal.BIT0 = 0;
	holeWithoutMetal.BIT1 = 0;
	holeWithoutMetal.BIT2 = 0;

	holeWithMetal.ID = SignalID::NORMAL_ID;
	holeWithMetal.BIT0 = 0;
	holeWithMetal.BIT1 = 0;
	holeWithMetal.BIT2 = 0;

	invalid.ID = SignalID::INVALID_ID;
	holeWithMetal.BIT0 = 0;
	holeWithMetal.BIT1 = 0;
	holeWithMetal.BIT2 = 0;

	signalArrayShortestPath[0] = { holeWithoutMetal, 0, 0, 0 };
	signalArrayShortestPath[1] = { holeWithoutMetal, 0, 0, 0 };
	signalArrayShortestPath[2] = {    holeWithMetal, 1, 0, 0 };

	signalArrayAllSignals[0] = {         bitCode1, 0, 0, 0 };
	signalArrayAllSignals[1] = {         bitCode2, 0, 0, 0 };
	signalArrayAllSignals[2] = {         bitCode4, 0, 0, 0 };
	signalArrayAllSignals[3] = {         bitCode5, 0, 0, 0 };
	signalArrayAllSignals[4] = {          flipped, 0, 0, 0 };
	signalArrayAllSignals[6] = {    holeWithMetal, 0, 0, 0 };
	signalArrayAllSignals[7] = {          invalid, 0, 0, 0 };
	signalArrayAllSignals[8] = { holeWithoutMetal, 0, 0, 0 };

	return 1;
}

AFTER(TestPuckSort) {
	delete context;
	return 1;
}

TEST_IMPL(TestPuckSort, test1) {
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayShortestPath) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(signalArrayShortestPath[arrayIterator]);

		if ( returnVal != returnArrayShortestPath[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}

TEST_IMPL(TestPuckSort, test2) {
	for ( uint8_t arrayIterator = 0; arrayIterator < sizeof(signalArrayAllSignals) / sizeof(PuckType); ++arrayIterator ) {
		bool returnVal = context->process(signalArrayAllSignals[arrayIterator]);

		if ( returnVal != returnArrayAllSignalsStart[arrayIterator] ) {
			return TEST_FAILED;
		}
	}
	return TEST_PASSED;
}
