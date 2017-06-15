//
// Created by Silt on 23.04.2017.
//

#ifndef SE2_CAL_TEST_H
#define SE2_CAL_TEST_H

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

#include <iostream>

class MachineOne : public TestCase {
public:
    MachineOne(int id, std::string brief): TestCase(id, brief){};
protected:
    TEST(Calibrate);
    TEST_CASE_METHODS
};


#endif //SE2_CAL_TEST_H
