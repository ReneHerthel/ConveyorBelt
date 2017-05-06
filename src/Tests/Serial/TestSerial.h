//
// Created by Silt on 06.05.2017.
//

#ifndef CONVEYORBELT_TESTSERIAL_H
#define CONVEYORBELT_TESTSERIAL_H


#include "../../TestFramework/TestCase.h"
#include "../../SerialPort/SerialSender.h"

class TestSerial : public TestCase {
public:
    TestSerial(int id, std::string brief): TestCase(id, brief){};
protected:
    TEST(SerialWriterTest);
    TEST_CASE_METHODS;
};


#endif //CONVEYORBELT_TESTSERIAL_H
