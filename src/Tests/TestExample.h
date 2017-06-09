//
// Created by Silt on 23.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTEXAMPLE_H
#define SE2_TEST_FRAMEWORK_TESTEXAMPLE_H


#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

#include <iostream>

class TestExample : public TestCase{
public:
    TestExample(int id, std::string brief): TestCase(id, brief){};
protected:
    int32_t testint = 12345;
    TEST(test1);
    TEST(test2);
    TEST(test3);
    TEST_CASE_METHODS
};


#endif //SE2_TEST_FRAMEWORK_TESTEXAMPLE_H
