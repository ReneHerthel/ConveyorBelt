#include <iostream>
#include "TestFramework.h"
#include "TestCase.h"
#include "TestExample.h"
#include "TestSuite.h"

using namespace std;

int main() {

    TestSuite ts;
    ts.REG_TESTCASE(new TestExample(1, "This is an example"));
    ts.REG_TESTCASE(new TestExample(2, "This is another one"));
    ts.REG_TESTCASE(new TestExample(3, "And a third one"));
    ts.START_TEST(ALL, "F:\\tstest.txt");
    return 0;
}
