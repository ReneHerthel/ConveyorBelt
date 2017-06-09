//
// Created by Silt on 23.04.2017.
//

#ifndef SE2_TIMER_TEST_H
#define SE2_TIMER_TEST_H

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

#include <iostream>

class TimerTest : public TestCase{
public:
    TimerTest(int id, std::string brief): TestCase(id, brief){};
protected:
    int32_t testint = 12345;
    TEST(TestSeconds);
    TEST_CASE_METHODS
};


#endif //SE2_TIMER_TEST_H
