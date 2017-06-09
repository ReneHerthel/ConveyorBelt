//
// Created by Silt on 23.04.2017.
//

#include "TimerTest.h"
#include "TimerService.h"
#include <stdint.h>
#include "PulseMessageReceiverService.cpp"

SETUP(TimerTest){
    REG_TEST(test1, 1, "Test1 Brief");
};

BEFORE_TC(TimerTest){return 1};

AFTER_TC(TimerTest){return 1;};

BEFORE(TimerTest){ return 1;};

AFTER(TimerTest){return 1;};

TEST_IMPL(TimerTest, TestSeconds){
	uint32_t MILLISECONDS = 1500; //1.5 Seconds
	int8_t code = 123;
	int32_t value = 456;
	int chid;

	PulseMessageReceiverService pmr;
	chid = pmr.newChannel();

	TimerService timer(chid, code);

	TimerService.setAlarm(MILLISECONDS, value);

	return TEST_FAILED;
}
