//
// Created by Silt on 25.05.2017.
//

#ifndef CONVEYORBELT_SERIALPROTOCOLLTEST_H
#define CONVEYORBELT_SERIALPROTOCOLLTEST_H


#include "../../TestFramework/TestCase.h"

class SerialProtocollTest : public TestCase{
    public:
        SerialProtocollTest(int id, std::string brief): TestCase(id, brief){};
    protected:
        TEST(WrapObject);
        TEST(TestSimpleMessages);
        TEST_CASE_METHODS
};


#endif //CONVEYORBELT_SERIALPROTOCOLLTEST_H
