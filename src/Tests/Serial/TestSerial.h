//
// Created by Silt on 06.05.2017.
//

#ifndef CONVEYORBELT_TESTSERIAL_H
#define CONVEYORBELT_TESTSERIAL_H

#include "../../TestFramework/TestCase.h"
#include "../../TestFramework/TestFramework.h"
#include "../../SerialPort/SerialSender.h"
#include "../../SerialPort/SerialReceiver.h"
#include "SerialTestStub.h"

#include <iostream>

class TestSerial : public TestCase{
public:
    TestSerial(int id, std::string brief): TestCase(id, brief){};
protected:
    int32_t testint = 12345;
    TEST(SerialWriterTest);
    TEST(OpenSernderReceiver);
    TEST(ReadWrite);
    TEST(Serilizeable);
    TEST_CASE_METHODS
};

#endif //CONVEYORBELT_TESTSERIAL_H
