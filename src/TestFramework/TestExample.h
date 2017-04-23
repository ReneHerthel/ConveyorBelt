//
// Created by Silt on 23.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTEXAMPLE_H
#define SE2_TEST_FRAMEWORK_TESTEXAMPLE_H


#include "TestCase.h"

class TestExample : public TestCase{
protected:
    TEST(test1);
    TEST(test2);
    TEST(test3);
protected:
    TEST_CASE_METHODS
};


#endif //SE2_TEST_FRAMEWORK_TESTEXAMPLE_H
