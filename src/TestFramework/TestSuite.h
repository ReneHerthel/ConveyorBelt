//
// Created by Silt on 20.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTSUITE_H
#define SE2_TEST_FRAMEWORK_TESTSUITE_H

#include <vector>
#include "TestFramework.h"
#include "TestCase.h"
#include <iostream>
#include <fstream>
#include <math.h>

struct tsTestCase{
    TestCase* tc; //pointer because abstract
    testResu resu; //this is unused, but could come in handy later
};

class TestSuite {
private:
    logLvl logl; //!< The logLvl used in all TestCases
    std::ostream* logstream; //!< stream to a ostream, one of theses is used
    std::fstream logfile; //!< stream to a file
    struct testResu resuSummary = {0,0,0}; //!<Summary of all TestCases
    std::vector<struct tsTestCase> tcs; //!<List of all TestCases
    std::queue<int32_t> testsToRun; //!< The Tests to run as choosen by chooseTestCase();

    void summary();
    void chooseTestCase();
    void printAllTestCases();
    void openLog(std::string log_path);
    void runTests();
    void printSeperator();
    logLvl chooseLogLvl();
public:
    void run(std::string loh_path);
    /**
     * @Brief Register new TesCase, USE DEFINE IN TestFramework.h
     * Register a new TestCase to the TestSuite
     * @param tc the Testcase
     */
    void registerTc(TestCase* tc);
};


#endif //SE2_TEST_FRAMEWORK_TESTSUITE_H
