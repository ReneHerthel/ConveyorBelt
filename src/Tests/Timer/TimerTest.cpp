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

	//TimerService timer_detlef(chid, code);

	//timer_detlef.setAlarm(milsec, value);

	ITimer *timer = new TimerService(chid, code);

	try {
		timer->setAlarm(milsec, value);
	} catch(int exception) {
		std::cout << "Timer error is: " + exception << std::endl;
	}



	msg = pmr.receivePulseMessage();

	std::cout << "worked" << std::endl;
	if(msg.code == code && msg.value == value){
		return TEST_PASSED;
	}

	return TEST_FAILED;
}
