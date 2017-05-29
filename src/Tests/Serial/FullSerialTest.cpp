//
// Created by Silt on 25.05.2017.
//

#include "FullSerialTest.h"
#include "SerialTestStub.h"
#include "../../SerialPort/TopLevelProto/SerialProtocoll.h"
#include "../../SerialPort/TopLevelProto/ITopLvlProtocoll.h"
#include "../../Wrapper/PulseMessageReceiver/IPulseMessageReceiver.h"
#include "../../Wrapper/PulseMessageReceiver/PulseMessageReceiverService.h"
#include "../../Wrapper/PulseMessageSender/IPulseMessageSender.h"
#include "../../Wrapper/PulseMessageSender/PulseMessageSenderService.h"

SETUP(FullSerialTest){
    REG_TEST(WrapObject, 1, "[SerialProtocol][SerialTestStub]Test to frame and deframe an object");
    REG_TEST(TestSimpleMessages, 2, "[SerialProtocol] Passing the simple messages");
}

TEST_IMPL(FullSerialTest, SimpleSerialMsg){
	PulseMessageReceiverService pmr();
	pmr.newChannel();

};

//v UNUSED v//
BEFORE(SerialProtocollTest){return 0;}
AFTER(SerialProtocollTest){return 0;}
BEFORE_TC(SerialProtocollTest){return 0;}
AFTER_TC(SerialProtocollTest){return 0;}
