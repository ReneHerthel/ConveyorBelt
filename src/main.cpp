#include <iostream>
#include "TestFramework/TestFramework.h"
#include "Tests/TestExample.h"
#include "Tests/PulseMessageWrapper/TestPulseMessageWrapper.h"
#include "Tests/HeightMeasurementStatemachine/TestHeightMeasurementStatemachine.h"
#include "Tests/EmbeddedRecorderBuffer/TestRecordBuffer.h"
#include "Tests/EmbeddedRecorder/TestEmbeddedRecorder.h"
#include "TestFramework/TestSuite.h"

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
    //ts.REG_TESTCASE(new TestExample(1, "This is an example"));
    //ts.REG_TESTCASE(new TestExample(2, "This is another one"));
    //ts.REG_TESTCASE(new TestExample(3, "And a third one"));
    // END Example Tests

    // PulseMessageWrapper tests
    ts.REG_TESTCASE(new TestPulseMessageWrapper(1, "Send and Receive pulse messages"));

    // HeightMeasurement tests
    ts.REG_TESTCASE(new TestHeightMeasurementStatemachine(2, "Make transitions through the statemachine of every type of puck"));

	// Ringbuffer tests
	ts.REG_TESTCASE(new TestRecordBuffer(3, "Test the functionality of the ringbuffer."));

	// EmbeddedRecorder
	ts.REG_TESTCASE(new TestEmbeddedRecorder(4, "Test the functionality of the EmbeddedRecorder."));

    //########################################//
    //##THIS STARTS THE TESTS, DO NOT TOUCH ##//
    //########################################//
    ts.START_TEST("/TEST_RESULT.txt");
    return 0;
}
