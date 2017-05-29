//
// Created by Silt on 25.05.2017.
//

#ifndef CONVEYORBELT_FullSerialTest_H
#define CONVEYORBELT_FullSerialTest_H


#include "TestCase.h"
#include "Serial.h"
#include "ITopLvlProtocoll.h"
#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"
#include "IPulseMessageSender.h"
#include "PulseMessageSenderService.h"

class FullSerialTest : public TestCase{
    public:
		FullSerialTest(int id, std::string brief): TestCase(id, brief){};
    protected:
        TEST(SimpleSerialMsg);
        TEST_CASE_METHODS
    private:
        Serial *sender;
        Serial *receiver;
};


#endif //CONVEYORBELT_FullSerialTest_H
