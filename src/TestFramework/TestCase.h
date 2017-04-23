//
// Created by Silt on 20.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTCASE_H
#define SE2_TEST_FRAMEWORK_TESTCASE_H


#include <gmon.h>
#include <string>
#include <list>
#include <fstream>
#include "TestFramework.h"

class TestCase {
public:
    testResu run(logLvl logl, std::string log_path);
protected:
    std::list<test> tests;
    int32_t id;
    std::string brief;

    virtual int32_t setup() = 0;
    void  registerTest(testFct fct, int32_t id, std::string brief);

    void setTCid(int32_t id);
    void setTCbrief(std::string brief);

    virtual int32_t beforeTC() = 0;
    virtual int32_t afterTC() = 0;

    virtual int32_t before() = 0;
    virtual int32_t after() = 0;

private:
    testResu resu;
    std::fstream logfile;
    bool logToFile;
    void logTest(test tst, std::string msg);
};


#endif //SE2_TEST_FRAMEWORK_TESTCASE_H
