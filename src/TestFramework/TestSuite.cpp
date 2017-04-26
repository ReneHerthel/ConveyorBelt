//
// Created by Silt on 20.04.2017.
//


#include <iomanip>
#include "TestSuite.h"
using namespace std;

void TestSuite::run(logLvl logl, std::string log_path) {

    if(log_path != STD_LOG){
        logfile.open(log_path, std::fstream::out); //open logfile
        if(logfile.fail()){
            std::cout << "Opening logfile failed" << std::endl;
            logstream = STD_LOG_STREAM;
        }
        logstream = &logfile;
    } else {
        logstream = STD_LOG_STREAM; //default log
    }

    int nbrOfTests = tcs.size();
    for(int i = 0; i < nbrOfTests; i++) {  //for each test registered
        struct testResu tcResu = (*tcs.front().tc).run(logl, logstream);
        resuSummary.failed += tcResu.failed;
        resuSummary.warning += tcResu.warning;
        resuSummary.passed += tcResu.passed;

    }
    summary();
}

void TestSuite::registerTc(TestCase* tc) {
    testResu tst = {0,0,0};
    tsTestCase tsTC = {tc, tst};
    tcs.push_back(tsTC);
}

void TestSuite::summary() {
    double passed = ((double)resuSummary.passed / (double)(resuSummary.failed + resuSummary.passed + resuSummary.warning))*100;
    (*logstream)<<  "\nSUMMARY OF TEST: " << std::setprecision (4) << passed << "% passed" //precision so that xx.yy %
                << "\nFailed: \t" << resuSummary.failed
                << "\nWarning:\t" << resuSummary.warning
                << "\nPassed: \t"  << resuSummary.passed << endl;
    (*logstream).flush();
}


