//
// Created by Silt on 20.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTSUITE_H
#define SE2_TEST_FRAMEWORK_TESTSUITE_H

#include <list>
#include "TestFramework.h"
#include "TestCase.h"
#include <iostream>
#include <fstream>

struct tsTestCase{
    TestCase* tc; //pointer becouse abstract
    testResu resu;
};

class TestSuite {
private:
    logLvl logl;
    std::ostream* logstream;
    std::fstream logfile;
    struct testResu resuSummary = {0,0,0};
    std::list<struct tsTestCase> tcs;
    void summary();
public:
    void run(logLvl, std::string loh_path);
    void registerTc(TestCase* tc);
};


#endif //SE2_TEST_FRAMEWORK_TESTSUITE_H
