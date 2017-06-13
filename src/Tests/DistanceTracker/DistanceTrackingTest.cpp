//
// Created by Silt on 23.04.2017.
//

#include "DistanceTrackingTest.h"
#include "DistanceTracker.h"
#include "DistanceEnum.h"
#include "DistanceObservable.h"
#include "PulseMessageReceiverService.h"
#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "Calibration.h"
#include "logger.h"
#include "logscope.h"

SETUP(DistanceTrackingTest){
	REG_TEST(SimpleTest, 1, "Just Create some distance trackers an let them run (no changes on the way)");
	REG_TEST(ChangeSpeed, 2, "Create a distance tracker, start it, and change speed in the middle of the run");
	REG_TEST(StopBelt, 3, "Create a distance tracker, start it, stop is, and resume it");
};

BEFORE_TC(DistanceTrackingTest){
	Calibration& cal = Calibration::getInstance();
	cal.manualCalibration(1000, 2000, 1, 1, 1, 1, 100, 200); //TIME 1000MS, fast twice as fast as slow
	cal.print();
	return 1;
}

AFTER_TC(DistanceTrackingTest){return 1;}

BEFORE(DistanceTrackingTest){return 1;}

AFTER(DistanceTrackingTest){return 1;}

using namespace DistanceSpeed;

TEST_IMPL(DistanceTrackingTest, SimpleTest){
	LOG_SCOPE;
	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.updateSpeed(FAST);

	//INI COM CHANNEL
	int8_t tr1Code = 123;
	int32_t tr1Value = 987;

	int8_t tr2Code = 123;
	int32_t tr2Value = 987;

	int chid;
	rcv::msg_t msg;
	rcv::PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	//INIT TR1
	DistanceTracker tr1(chid, tr1Code);
	auto startTr1 = std::chrono::system_clock::now();
	tr1.startAlarm(tr1Value, INLET_TO_HEIGHT, 1);

	msg = pmr.receivePulseMessage();
	auto endTr1 = std::chrono::system_clock::now();
	if(msg.code != tr1Code || msg.value != tr1Value){ //right code and value?
		LOG_ERROR << "tr1 Code of Value Failed \n";
		return TEST_FAILED;
	}

	std::chrono::duration<double> diffTr1 = endTr1-startTr1;
	if(!(diffTr1.count() > 0.99 && diffTr1.count() < 1.01)){ //right time (with delta of 10%)
		LOG_ERROR << "tr1 time failed " << diffTr1.count() << "\n";
		return TEST_FAILED;
	}

	distO.updateSpeed(SLOW);

	//INIT TR2
	DistanceTracker tr2(chid, tr2Code);
	auto startTr2 = std::chrono::system_clock::now();
	tr1.startAlarm(tr2Value, INLET_TO_HEIGHT,  1);

	msg = pmr.receivePulseMessage();
	auto endTr2 = std::chrono::system_clock::now();
	if(msg.code != tr2Code || msg.value != tr2Value){ //right code and value?
		LOG_ERROR << "tr2 Code of Value Failed \n";
		return TEST_FAILED;
	}

	std::chrono::duration<double> diffTr2 = endTr2-startTr2;
	if(!(diffTr2.count() > 1.9 && diffTr2.count() < 2.1)){ //right time (with delta of 10%)
		LOG_ERROR << "tr2 time failed " << diffTr2.count() << "\n";
		return TEST_FAILED;
	}

	std::cout << "Tr1: " << diffTr1.count() << "s Tr2: " << diffTr2.count() << std::endl;

	return TEST_PASSED;
}

TEST_IMPL(DistanceTrackingTest, ChangeSpeed){
	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.updateSpeed(FAST);


	//INI COM CHANNEL
	int8_t code = 123;
	int32_t value = 987;

	int chid;
	rcv::msg_t msg;
	rcv::PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	//INIT TR1
	DistanceTracker tr1(chid, code);
	auto start = std::chrono::system_clock::now();
	tr1.startAlarm(value, INLET_TO_HEIGHT, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //After 500ms passed, change speed
	distO.updateSpeed(SLOW);

	msg = pmr.receivePulseMessage();
	auto end = std::chrono::system_clock::now();
	if(msg.code != code || msg.value != value){ //right code and value?
		return TEST_FAILED;
	}

	std::chrono::duration<double> diff= end-start;
	if(!(diff.count() > 1.49 && diff.count() < 1.51)){ //right time (with delta of 10%)
		LOG_ERROR << "ChangeSpeed time was: " << diff.count() << "s\n";
		return TEST_FAILED;
	}

	return TEST_PASSED;
}

TEST_IMPL(DistanceTrackingTest, StopBelt){
	DistanceObservable& distO = DistanceObservable::getInstance();
	distO.updateSpeed(FAST);


	//INI COM CHANNEL
	int8_t code = 123;
	int32_t value = 987;

	int chid;
	rcv::msg_t msg;
	rcv::PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	//INIT TR1
	DistanceTracker tr1(chid, code);
	auto start = std::chrono::system_clock::now();
	tr1.startAlarm(value, INLET_TO_HEIGHT, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //After 500ms passed, change speed
	distO.updateSpeed(STOP);
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //After 500ms passed, change speed
	distO.updateSpeed(SLOW);

	msg = pmr.receivePulseMessage();
	auto end = std::chrono::system_clock::now();
	if(msg.code != code || msg.value != value){ //right code and value?
		return TEST_FAILED;
	}

	std::chrono::duration<double> diff= end-start;
	if(!(diff.count() > 1.9 && diff.count() < 2.1)){ //right time (with delta of 10%)
		LOG_ERROR << "Stop time was: " << diff.count() << "s\n";
		return TEST_FAILED;
	}

	return TEST_PASSED;
}



