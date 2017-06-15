//
// Created by Silt on 23.04.2017.
//

#ifndef MACHINE_ONE_TEST_H
#define MACHINE_ONE_TEST_H

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

#include <iostream>

class MachineOne : public TestCase {
public:
    MachineOne(int id, std::string brief): TestCase(id, brief){};
protected:
    TEST(programm_m1);
    TEST_CASE_METHODS
};


#endif //MACHINE_ONE_TEST_H
