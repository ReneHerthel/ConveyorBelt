//
// Created by Silt on 25.05.2017.
//

#include "FullSerialTest.h"
#include "SerialTestStub.h"
#include "SerialProtocoll.h"
#include "Logger.h"
#include <iostream>
#include <stdlib.h>

SETUP(FullSerialTest){
    REG_TEST(SimpleSerialMsg, 1, "[Serial]Send one msg (stop)");
}

TEST_IMPL(FullSerialTest, SimpleSerialMsg){
	PulseMessageReceiverService pmr;
	int chid_out = pmr.newChannel(); //receive from this channel from serial

	PulseMessageReceiverService workaround;
	int chid_in = workaround.newChannel(); //receive from this channel from serial

	PulseMessageSenderService pms(chid_in);


	char sender_node[] = "/dev/ser1";
	char receiver_node[] = "/dev/ser2";

	//Init serial1
	SerialSender sender_s(sender_node);
	//sender_s.reset();
	SerialReceiver receiver_s(sender_node);
	receiver_s.reset();
	SerialProtocoll proto_s = SerialProtocoll(SENDER);
	Serial serial_s(receiver_s, sender_s, proto_s, chid_in, chid_out);

	//Init serial2
	SerialSender sender_r(receiver_node);
	//sender_r.reset();
	SerialReceiver receiver_r(receiver_node);
	receiver_r.reset();
	SerialProtocoll proto_r = SerialProtocoll(RECEIVER);
	Serial serial_r(receiver_r, sender_r, proto_r, chid_in, chid_out);

	LOG_DEBUG << "Send pulse \n";

	pms.sendPulseMessage(SER_OUT,STOP);

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
