//
// Created by Silt on 20.04.2017.
//

#include <iostream>
#include "TestCase.h"
#include <fstream>

testResu TestCase::run(logLvl logl, std::ostream* logfile) {
    logstream = logfile;
    setup();
    beforeTC();
    (*logstream)<< "\nTEST_" << id << ":::" << brief  << std::endl;
    int nbrOfTests = tests.size();
    for(int i = 0; i < nbrOfTests; i++){  //for each test registered
        before();
        test curTest = tests.front();
        int32_t tstResu= (this->*curTest.fct)();//call memeber funktion

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
            logTest(curTest, msg);
        }
        tests.pop_front(); //remove executed test
        after();
    }
    afterTC();
    return resu; //done
}

void TestCase::logTest(test tst, std::string msg) {
    (*logstream)<< tst.id << "| " << tst.brief << " => "<< msg << std::endl;
}


void TestCase::setTCid(int32_t id) {
    this->id = id;
}

void TestCase::setTCbrief(std::string brief) {
    this->brief =  brief;
}

void TestCase::registerTest(testFct fct, int32_t id, std::string brief) {
    test new_test = {fct, id, brief};
    tests.push_back(new_test);
}







