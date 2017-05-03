#include <iostream>
#include "TestFramework/TestFramework.h"
#include "TestExample.h"
#include "TestSuite.h"

using namespace std;

int main() {
	//################################################################################//
	//## THIS IS THE TEST MAIN, ADD A TEST FOR YOUR MODULE INSTEAD OF WRITING A MAIN##//
	//################################################################################//
    TestSuite ts;
    //^ DO NOT TOUCH ^//

    //######################################################//
    //## REGISTER YOUR TESTS HERE LIKE THIS EXAMPLE SHOWS ##//
    //######################################################//

    //TEST FOR: Example Tests
    ts.REG_TESTCASE(new TestExample(1, "This is an example"));
    ts.REG_TESTCASE(new TestExample(2, "This is another one"));
    ts.REG_TESTCASE(new TestExample(3, "And a third one"));
    // END Example Tests


    //########################################//
    //##THIS STARTS THE TESTS, DO NOT TOUCH ##//
    //########################################//
    ts.START_TEST("/TEST_RESULT.txt");
    return 0;
}
