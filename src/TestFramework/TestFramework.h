//
// Created by Silt on 21.04.2017.
//

#ifndef SE2_TEST_FRAMEWORK_TESTFRAMEWORK_H
#define SE2_TEST_FRAMEWORK_TESTFRAMEWORK_H

#include <string>
#include <stdint.h>

struct testResu{
    int32_t passed;
    int32_t failed;
    int32_t warning;
};

typedef int32_t  logLvl;

#define STD_LOG "stdlog"
#define STD_LOG_STREAM &std::cout

/////////////Test Results///////////
#define TEST_FAILED (-1)
#define TEST_ALL (0) //Not a test result, used to determin log Levels
#define TEST_WARNING (2)
#define TEST_PASSED (1)

//////////////TestSuite Defs start here//////////////
#define REG_TESTCASE(x) registerTc(x); /*!<Use to register your Testcase to the TestSuite */
#define START_TEST(y) run(y); /*!<  Use to start the testsuite */

/////////////TestCase Defs start Here//////////////

#define SETUP(TC) int32_t TC::setup() /*!< Use to define your setup funktion */
#define REG_TEST(fct, id, brief) registerTest([&](){return (*this).fct();}, id, brief) /*!< Use to register yozur tests to the Testcase in the Setup funktion*/

#define TEST(name) int32_t name(void) /*!< Use to declare a test in the header file */
#define TEST_IMPL(TC, name) int32_t TC::name(void) /*!< Use to define your test in the cpp file*/

#define BEFORE(TC) int32_t TC::before() /*!< Use to define the function executet before evrey test*/
#define AFTER(TC) int32_t TC::after() /*!< Use to define the function executet after evrey test*/

#define BEFORE_TC(TC) int32_t TC::beforeTC() /*!< Use to define your before TestCase function */
#define AFTER_TC(TC) int32_t TC::afterTC() /*!< Use to define your after TestCase function */

#define TEST_CASE_METHODS \
int32_t setup(); \
int32_t beforeTC(); \
int32_t afterTC(); \
int32_t before(); \
int32_t after(); /*!< Contains all methods that a Test must implement, use in the header */

#endif //SE2_TEST_FRAMEWORK_TESTFRAMEWORK_H
