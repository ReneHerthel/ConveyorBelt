//
// Created by Silt on 20.04.2017.
//

#include "TestCase.h"

TestCase::TestCase(int id, std::string brief) {
    this->id = id;
    this->brief = brief;
}

testResu TestCase::run(logLvl logl, std::ostream* logfile) {
    logstream = logfile;
    setup();
    beforeTC();
    printInfo(logstream);
    int nbrOfTests = tests.size();
    for(int i = 0; i < nbrOfTests; i++){  //for each test registered
        before();
        int32_t tstResu= tests[i].fct();//call memeber funktion

        std::string msg;
        switch(tstResu){ //determin results
            case PASSED:
                msg = "PASSED";
                resu.passed++;
                break;
            case WARNING:
                msg = "WARNING";
                resu.warning++;
                break;
            case FAILED:
                msg = "FAILED";
                resu.failed++;
                break;
            default: msg = "Unknown Result";
        }
        if(tstResu == logl or logl == ALL){ //log result? (log lvl)
            logTest(tests[i], msg);
        }
        after();
    }
    afterTC();
    return resu; //done
}

void TestCase::logTest(test tst, std::string msg) {
    (*logstream)<< tst.id << "| " << tst.brief << " => "<< msg << std::endl;
}

void TestCase::registerTest(testFct fct, int32_t id, std::string brief) {
    test new_test = {fct, id, brief};
    tests.push_back(new_test);
}

void TestCase::printInfo(std::ostream *log) {
    (*log)<< "TEST_" << id << "  " << brief  << std::endl;
}









