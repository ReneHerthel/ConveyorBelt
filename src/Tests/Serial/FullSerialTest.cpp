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
    REG_TEST(SimpleSerialMsg, 1, "[Serial]Send one msg (stop)");
}

TEST_IMPL(FullSerialTest, SimpleSerialMsg){
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG << "Serial test1 \n";
	PulseMessageReceiverService pmr;
	int chid_out = pmr.newChannel(); //receive from this channel from serial

	PulseMessageReceiverService workaround;
	int chid_in = workaround.newChannel(); //send to serial on this one


	//Sender doesnt need to reply, receiver doesnt need to listen, create dummy channels
	PulseMessageReceiverService dummy_r;
	int chid_dummy_r = workaround.newChannel();
	PulseMessageReceiverService dummy_s;
	int chid_dummy_s = workaround.newChannel();

	PulseMessageSenderService pms(chid_in);


	char sender_node[] = "/dev/ser1";
	char receiver_node[] = "/dev/ser2";

	pms.sendPulseMessage(SER_OUT,STOP);

	//Init serial1
	SerialSender sender_s(sender_node);
	//sender_s.reset();
	SerialReceiver receiver_s(sender_node);
	receiver_s.reset();
	SerialProtocoll proto_s = SerialProtocoll(SENDER);
	Serial *serial_s = new Serial(receiver_s, sender_s, proto_s, chid_in, chid_dummy_s);

	std::thread ser1(*serial_s);

	LOG_DEBUG << "Serial1 init \n";

	//Init serial2
	SerialSender sender_r(receiver_node);
	//sender_r.reset();
	SerialReceiver receiver_r(receiver_node);
	receiver_r.reset();
	SerialProtocoll proto_r = SerialProtocoll(RECEIVER);
	Serial *serial_r = new Serial(receiver_r, sender_r, proto_r, chid_dummy_r, chid_out);

	std::thread ser2(*serial_r);

	LOG_DEBUG << "Send pulse \n";

	IPulseMessageReceiver::rcv_msg_t msg = pmr.receivePulseMessage();

	LOG_DEBUG << "Received Pulse \n";

	std::cout << "Code: " << msg.code << " Value: " << msg.code << std::endl;



	return TEST_FAILED;
};

//v UNUSED v//
BEFORE(FullSerialTest){return 0;}
AFTER(FullSerialTest){return 0;}
BEFORE_TC(FullSerialTest){return 0;}
AFTER_TC(FullSerialTest){return 0;}
