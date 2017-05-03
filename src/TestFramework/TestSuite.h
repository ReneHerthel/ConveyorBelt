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
    TestCase* tc; //pointer becouse abstract
    testResu resu; //this is unused, but could come in handy later
};

class TestSuite {
private:
    logLvl logl;
    std::ostream* logstream;
    std::fstream logfile;
    struct testResu resuSummary = {0,0,0};
    std::vector<struct tsTestCase> tcs;
    std::queue<int32_t> testsToRun; //!< The Tests to run as choosen by chooseTestCase();

    void summary();
    void chooseTestCase();
    void printAllTestCases();
    void openLog(std::string log_path);
    void runTests();
    void printSeperator();
public:
    void run(logLvl, std::string loh_path);
    void registerTc(TestCase* tc);
};


#endif //SE2_TEST_FRAMEWORK_TESTSUITE_H
