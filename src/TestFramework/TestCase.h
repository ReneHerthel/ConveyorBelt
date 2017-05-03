//
// Created by Silt on 20.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTCASE_H
#define SE2_TEST_FRAMEWORK_TESTCASE_H


#include <string>
#include <list>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include "TestFramework.h"
#include <stdint.h>

class TestCase {
public:
    typedef  std::function<int32_t(void)> testFct; //Define a funtionpointer type test, takes no argument, return int, maybe this needs TestCase::

    struct test{ //
        testFct fct;
        int32_t id;
        std::string brief;
    };

    TestCase(int id, std::string brief);

    /**
     * @brief run the TestCase
     * This Method runs all the Tests in the TestCase and writes it into the log file.
     * @param logl The Log Level (Log Failed, Passed or all Tests)
     * @param logfile The log file that will be used to store test result
     * @return Summary TestCase Result
     */
    testResu run(logLvl logl, std::ostream* logfile);
    void printInfo(std::ostream* log);
protected:
    std::vector<test> tests;
    int32_t id;
    std::string brief;

    virtual int32_t setup() = 0;
    void  registerTest(std::function<int32_t(void)> fct, int32_t id, std::string brief);

    virtual int32_t beforeTC() = 0;
    virtual int32_t afterTC() = 0;

    virtual int32_t before() = 0;
    virtual int32_t after() = 0;

private:
    testResu resu = {0,0,0}; //At the beginning, nothing passed
    std::ostream* logstream;

    void logTest(test tst, std::string msg);
};


#endif //SE2_TEST_FRAMEWORK_TESTCASE_H
