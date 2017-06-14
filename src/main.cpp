#include <iostream>
#include "TestFramework/TestFramework.h"
#include "Tests/TestExample.h"
#include "Tests/PulseMessageWrapper/TestPulseMessageWrapper.h"
#include "Tests/HeightMeasurementStatemachine/TestHeightMeasurementStatemachine.h"
#include "TestFramework/TestSuite.h"
#include "LightSystemTest.h"
#include "Tests/Serial/TestSerial.h"
#include "Tests/Serial/SerialProtocollTest.h"
#include "FullSerialTest.h"
#include "Logger/Logger.h"
#include "TimerTest.h"
#include "DistanceTrackingTest.h"
#include "CalibrationTest.h"
#include "MeasurementHeightTest.h"

using namespace std;

int main() {
	//################################################################################//
	//## THIS IS THE TEST MAIN, ADD A TEST FOR YOUR MODULE INSTEAD OF WRITING A MAIN##//
	//################################################################################//
    TestSuite ts;
    LOG_SET_LEVEL(DEBUG);
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
    ts.REG_TESTCASE(new TestHeightMeasurementStatemachine(2, "Make transitions through the statemachine of every type of puck"))

    // LightSystem tests
    ts.REG_TESTCASE(new LightSystemTest(3, "LightSystem: Level: Operating"));

    //TEST FOR: Serial
    ts.REG_TESTCASE(new TestSerial(4, "[Serial] Basic Tests for Serial"));
    ts.REG_TESTCASE(new SerialProtocollTest(5, "[SerialProtocoll] Test for the toplvl prot"));
    ts.REG_TESTCASE(new FullSerialTest(6, "[Serial] Full Serial test"));

    //TIMER TESTS
    ts.REG_TESTCASE(new TimerTest(7, "[TimerService] Test timer accuracy and methods"));

    //DistanceTracking test
    ts.REG_TESTCASE(new DistanceTrackingTest(8, "[DistanceTracker][DistanceObservable] DistanceTracking test"));

    //Calibration Test
    ts.REG_TESTCASE(new CalibrationTest(9, "[Caibration]"));

    //Calibrate Heights
    ts.REG_TESTCASE(new MeasurementHeightTest(10, "[Man Height Cal]"));

    //########################################//
    //##THIS STARTS THE TESTS, DO NOT TOUCH ##//
    //########################################//
    ts.START_TEST("/TEST_RESULT.txt");
    return 0;
}
