//
// Created by Silt on 23.04.2017.
//

#include "TimerTest.h"
#include "TimerService.h"
#include <stdint.h>
#include "PulseMessageReceiverService.h"
#include <stdlib.h>

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

	try {
		timer.setAlarm(milsec, value);
	} catch(int exception) {
		std::cout << "Timer error is: " << exception << std::endl;
	}



	msg = pmr.receivePulseMessage();

	std::cout << "worked" << std::endl;
	if(msg.code == code && msg.value == value){
		return TEST_PASSED;
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

	milsecResu = timer.killAlarm();

	std::cout << "Should be arround 5500: " << milsecResu << std::endl;

	return TEST_FAILED;
}
