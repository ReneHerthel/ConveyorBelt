//
// Created by Silt on 23.04.2017.
//

#include "TimerTest.h"
#include "TimerService.h"
#include <stdint.h>
#include "PulseMessageReceiverService.h"
#include <stdlib.h>
#include <chrono>
#include <thread>

SETUP(TimerTest){
	REG_TEST(TestSeconds, 1, "Test1 Brief");
    REG_TEST(KillAlarm, 2, "Try to kill an Alarm");
};

BEFORE_TC(TimerTest){return 1;}

AFTER_TC(TimerTest){return 1;}

BEFORE(TimerTest){ return 1;}

AFTER(TimerTest){return 1;}

TEST_IMPL(TimerTest, TestSeconds){
	uint32_t milsec = 5500; //1.5 Seconds
	int8_t code = 123;
	int32_t value = 456;
	int chid;
	rcv::msg_t msg;
	rcv::PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	TimerService timer(chid, code);

	auto start = std::chrono::system_clock::now();
	try {
		timer.setAlarm(milsec, value);
	} catch(int exception) {
		std::cout << "Timer error is: " << exception << std::endl;
	}



	msg = pmr.receivePulseMessage();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;

	std::cout << "worked" << std::endl;
	if(msg.code == code && msg.value == value){
		if(diff.count() > 5.4 && diff.count() < 5.6){
			return TEST_PASSED;
		}
	}

	return TEST_FAILED;
}

TEST_IMPL(TimerTest, KillAlarm){
	uint32_t milsec = 5500; //5.5 Seconds
	uint32_t milsecResu = 0;
	int8_t code = 123;
	int32_t value = 456;
	int chid;
	rcv::msg_t msg;
	rcv::PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	TimerService timer(chid, code);

	try {
		timer.setAlarm(milsec, value);
	} catch(int exception) {
		std::cout << "Timer error is: " << exception << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(2));

	milsecResu = timer.killAlarm();

	if(milsecResu > 3490 && milsecResu < 3510){
		return TEST_PASSED;
	} else {
		return TEST_FAILED;
	}
}
