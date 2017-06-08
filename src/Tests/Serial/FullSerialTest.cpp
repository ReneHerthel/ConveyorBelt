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
	//REG_TEST(ConcurrentReceiver, 1, "[Serial]Send one msg (stop)");
    REG_TEST(SimpleSerialMsg, 2, "[Serial]Construct an kill 2 serials");
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
	msg = pmr.receivePulseMessage();
	std::cout << "Pulse Received" << std::endl;
	receiver.kill();

	rec_thread.join();


	cout.write((char*)msg.value, sizeof(testString));

	if(memcmp(testString, (char*)msg.value, sizeof(testString))==0){
		return TEST_PASSED;
	} else {
		return TEST_FAILED;
	}


}

TEST_IMPL(FullSerialTest, SerialPOLFailTest){
}

TEST_IMPL(FullSerialTest, SimpleSerialMsg){
	char ser1_path[] = "/dev/ser1";
	char ser2_path[] = "/dev/ser2";

	bool test_failed = false;


	//---------------INIT SER1---------------------
	//Init PMR
	rcv::PulseMessageReceiverService pmrSer1;
	int pmrSer1Chid = pmrSer1.newChannel();

	//Init PMS
	rcv::PulseMessageReceiverService pmsChannelCreatorSer1;
	int pmsSer1Chid = pmsChannelCreatorSer1.newChannel();
	PulseMessageSenderService pmsSer1(pmsSer1Chid);

	//Init Sender & Receiver
	SerialSender senderSer1(ser1_path);
	SerialReceiver receiverSer1(ser1_path);

	//Init Protocol
	SerialProtocoll protoSer1(SENDER);

	//Init Serial
	Serial ser1(receiverSer1, senderSer1, protoSer1, pmsSer1Chid, pmrSer1Chid);





	//---------------INIT SER2---------------------
	//Init PMR
	rcv::PulseMessageReceiverService pmrSer2;
	int pmrSer2Chid = pmrSer2.newChannel();

	//Init PMS
	rcv::PulseMessageReceiverService pmsChannelCreatorSer2;
	int pmsSer2Chid = pmsChannelCreatorSer2.newChannel();
	PulseMessageSenderService pmsSer2(pmsSer2Chid);

	//Init Sender & Receiver
	SerialSender senderSer2(ser2_path);
	SerialReceiver receiverSer2(ser2_path);

	//Init Protocol
	SerialProtocoll protoSer2(RECEIVER);

	//Init Serial
	Serial ser2(receiverSer2, senderSer2, protoSer2, pmsSer2Chid, pmrSer2Chid);

	//START THOSE BAD BOYS
	std::thread ser1_thread(ref(ser1));
	std::thread ser2_thread(ref(ser2));


	//------------TEST SIMPLE SIGNALS------------//
	uint32_t signal;
	rcv::msg_t msg;
	for(int i = 1; i <= 4; i++){ //Test 4 Simple signals
		switch(i){
			case 1: signal = ACCEPT; break;
			case 2: signal = STOP; break;
			case 3: signal = RESUME; break;
			case 4: signal = RECEIVED; break;
		}
		pmsSer1.sendPulseMessage(SER_OUT, signal);
		msg = pmrSer2.receivePulseMessage();

		if((uint32_t)msg.value != (uint32_t)signal){
			return TEST_FAILED;
		}
	}

	//------------TEST SENDING AN OBJ-----------//
	SerialTestStub testObj(10,20,30,0,40);
	Serialized serTestObj;

	serTestObj = testObj.serialize();


	ser1.kill();
	ser2.kill();

	ser1_thread.join();
	ser2_thread.join();

	return TEST_PASSED;

}

//v UNUSED v//
BEFORE(FullSerialTest){return 0;}
AFTER(FullSerialTest){return 0;}
BEFORE_TC(FullSerialTest){return 0;}
AFTER_TC(FullSerialTest){return 0;}
