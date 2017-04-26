#include <iostream>
#include <list>
#include "TestFramework.h"
#include "TestCase.h"
#include "TestExample.h"
#include "TestSuite.h"

using namespace std;

int main() {

    TestSuite ts;
    ts.TESTCASE(new TestExample);
    ts.START_TEST(ALL, "F:\\tstest.txt");
    return 0;
}
