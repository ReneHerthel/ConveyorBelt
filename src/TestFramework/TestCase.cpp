//
// Created by Silt on 20.04.2017.
//

#include <iostream>
#include "TestCase.h"
#include <fstream>

testResu TestCase::run(logLvl logl, std::string log_path) {
    if(log_path != STD_LOG){
        logfile.open(log_path, std::fstream::out);
        if(logfile.fail()){
            std::cout << "Opening logfile failed" << std::endl;
            logToFile = false;
        } else {
            logToFile = true;
        }
    }

    std::cout << "Now running" << std::endl;
    setup();
    beforeTC();
    int nbrOfTests = tests.size();
    for(int i = 0; i < nbrOfTests; i++){
        before();
        test curTest = tests.front();
        int32_t resu= curTest.fct();

        std::string msg;
        switch(resu){
            case PASSED: msg = "PASSED"; break;
            case WARNING: msg = "WARNING"; break;
            case FAILED: msg = "FAILED"; break;
            default: msg = "Unknown Result";
        }
        if(resu == logl or logl == ALL){
            logTest(curTest, msg);
        }
        tests.pop_front();
        after();
    }
    afterTC();
}

void TestCase::logTest(test tst, std::string msg) {
    if(logToFile){
        logfile << tst.id << "| " << tst.brief << " => "<< msg << std::endl;
    } else {
        std::cout << tst.id << "| " << tst.brief << " => "<< msg << std::endl;
    }
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







