//
// Created by Silt on 20.04.2017.
//

#include "TestSuite.h"
using namespace std;

void TestSuite::run(std::string log_path) {
    logl = chooseLogLvl();
    openLog(log_path);
    printAllTestCases();
    chooseTestCase();
    runTests();
    summary();
}

void TestSuite::registerTc(TestCase* tc) {
    testResu tst = {0,0,0};
    tsTestCase tsTC = {tc, tst};
    tcs.push_back(tsTC);
}

void TestSuite::summary() {
    double passed = ((double)resuSummary.passed / (double)(resuSummary.failed + resuSummary.passed + resuSummary.warning))*100;
    (*logstream)<<  "\nSUMMARY OF TEST: "  << passed << "% passed"
                << "\nFailed: \t" << resuSummary.failed
                << "\nWarning:\t" << resuSummary.warning
                << "\nPassed: \t"  << resuSummary.passed << endl;
    (*logstream).flush();
}

void TestSuite::chooseTestCase() {
    std::cout   <<"Enter the number of the test you want to Start"
                <<"you can have enter multiple tests by entering multiple numbers"
                <<"seperated by spaces \n"
                <<"Start the tests by typing [Any Key] and pressing enter or "
                <<"start all tests by entering no number" << std::endl;
    int32_t in = 0;
    do{
        in = 0;
        cin >> in;
        if(in > 0){
            if(in > tcs.size()){
                cout<< "Number" << in << "is nor in range" << endl;
            } else {
                testsToRun.push(in);
            }
        }
    }while(in > 0);

}

void TestSuite::printAllTestCases() {
    int index = 1;
    for(auto &i : tcs) {  //for each test registered
        std::cout << "[" << index << "]";
        i.tc->printInfo(&std::cout);
        index++;
    }
}

void TestSuite::openLog(std::string log_path) {
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
}

void TestSuite::runTests() {
    if(testsToRun.size() <= 0){
        int nbrOfTests = tcs.size();
        for(int i = 0; i < nbrOfTests; i++) {  //for each test registered
            struct testResu tcResu = tcs[i].tc->run(logl, logstream);
            resuSummary.failed += tcResu.failed;
            resuSummary.warning += tcResu.warning;
            resuSummary.passed += tcResu.passed;
            printSeperator();
        }
    } else {
        int i = 0;
        while (!testsToRun.empty()){ // every test choosen by user
            i = testsToRun.front()-1;
            testsToRun.pop();
            struct testResu tcResu = tcs[i].tc->run(logl, logstream);
            resuSummary.failed += tcResu.failed;
            resuSummary.warning += tcResu.warning;
            resuSummary.passed += tcResu.passed;
            printSeperator();
        }
    }

}

logLvl TestSuite::chooseLogLvl(){
	cout << "Choose wich Tests to log FAILED [-1] ALL [0] WARNING [2] PASSED [1]:" << std::endl;
	int32_t in;
	cin >> in;
	return (logLvl)in;
}

void TestSuite::printSeperator() {
    (*logstream)<<"--------------------\n"<<endl;
}


