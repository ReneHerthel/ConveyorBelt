//
// Created by Silt on 20.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTCASE_H
#define SE2_TEST_FRAMEWORK_TESTCASE_H


#include <string>
#include <list>
#include <fstream>
#include "TestFramework.h"
#include <stdint.h>

class TestCase {
public:

    struct test{
        testFct fct;
        int32_t id;
        std::string brief;
    };

    testResu run(logLvl logl, std::ostream* logfile);
protected:
    std::list<std::function<int32_t(void)>> tests;
    int32_t id;
    std::string brief;

    virtual int32_t setup() = 0;
    void  registerTest(std::function<int32_t(void)> fct, int32_t id, std::string brief);

    void setTCid(int32_t id);
    void setTCbrief(std::string brief);

    virtual int32_t beforeTC() = 0;
    virtual int32_t afterTC() = 0;

    virtual int32_t before() = 0;
    virtual int32_t after() = 0;

private:
    testResu resu = {0,0,0}; //At the beginning, nothing passed
    std::ostream* logstream;
    bool logToFile;
    void logTest(test tst, std::string msg);
};


#endif //SE2_TEST_FRAMEWORK_TESTCASE_H
