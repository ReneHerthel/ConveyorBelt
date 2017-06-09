//
// Created by Silt on 23.04.2017.
//

#ifndef SE2_DIST_H
#define SE2_DIST_H

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

#include <iostream>

class DistanceTrackingTest : public TestCase {
public:
    DistanceTrackingTest(int id, std::string brief): TestCase(id, brief){};
protected:
    TEST(SimpleTest);
    TEST(ChangeSpeed);
    TEST_CASE_METHODS
};


#endif //SE2_DIST_H
