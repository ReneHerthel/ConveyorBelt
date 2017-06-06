//
// Created by Silt on 25.05.2017.
//

#include "FullSerialTest.h"
#include "SerialTestStub.h"
#include "SerialProtocoll.h"
#include "Logger.h"
#include "Logscope.h"
#include <iostream>
#include <stdlib.h>
#include <thread>

SETUP(FullSerialTest){
	REG_TEST(ConcurrentReceiver, 1, "[Serial]Send one msg (stop)");
    //REG_TEST(SimpleSerialMsg, 2, "[Serial]Send one msg (stop)");
}

TEST_IMPL(FullSerialTest, ConcurrentReceiver){
	char sender_node[] = "/dev/ser1";
	char receiver_node[] = "/dev/ser2";
	rcv::msg_t msg;

	std::cout << "Opening" << std::endl;
	SerialSender sender(sender_node);
	SerialReceiver receiver(receiver_node);

	rcv::PulseMessageReceiverService pmr;
	int chid_out = pmr.newChannel();

	std::thread rec_thread(ref(receiver), chid_out);

	char testString[] = "START Flitzndafoer_123456 123123 END";
	sender.send(testString, sizeof(testString));

	std::cout << "Wait for pulse" << std::endl;
	pmr.receivePulseMessage();
	std::cout << "Pulse Received" << std::endl;
	receiver.kill();

	rec_thread.join();

	return TEST_PASSED;
}

TEST_IMPL(FullSerialTest, SimpleSerialMsg){
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG << "Serial test1 \n";
	rcv::PulseMessageReceiverService pmr;
	int chid_out = pmr.newChannel(); //receive from this channel from serial

	rcv::PulseMessageReceiverService workaround;
	int chid_in = workaround.newChannel(); //send to serial on this one
	PulseMessageSenderService pms(chid_in);


	char sender_node[] = "/dev/ser1";
	char receiver_node[] = "/dev/ser2";

	int testsig = STOP;
	pms.sendPulseMessage(SER_IN,(int)&testsig);


	//Init serial1
	SerialSender sender_s(sender_node);
	//sender_s.reset();
	SerialReceiver receiver_s(sender_node);
	receiver_s.reset();
	SerialProtocoll proto_s = SerialProtocoll(SENDER);
	Serial *serial_s = new Serial(receiver_s, sender_s, proto_s, chid_in, chid_out);

	//std::thread *sers = new thread((*serial_s));
	std::thread sers(*serial_s);

	LOG_DEBUG << "Send pulse \n";



	rcv::msg_t msg = pmr.receivePulseMessage();

	LOG_DEBUG << "Received Pulse \n";

	//std::cout << "Code: " << msg.code << " Value: " << msg.code << std::endl;

	sers.join();
	return TEST_FAILED;
};

//v UNUSED v//
BEFORE(FullSerialTest){return 0;}
AFTER(FullSerialTest){return 0;}
BEFORE_TC(FullSerialTest){return 0;}
AFTER_TC(FullSerialTest){return 0;}
