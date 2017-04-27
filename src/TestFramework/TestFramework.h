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

#define FAILED (-1)
#define ALL (0)
#define WARNING (2)
#define PASSED (1)

//////////////TestSuite Defs start here//////////////
#define TESTCASE(x) registerTc(x);
#define START_TEST(x,y) run(x,y);

/////////////TestCase Defs start Here//////////////
#define SETUP(TC) int32_t TC::setup()
#define REG_TEST(fct, id, brief) registerTest([&](){this.fct}, id, brief)

#define TEST(name) int32_t name(void)
#define TEST_IMPL(TC, name) int32_t TC::name(void)

#define SET_TEST_CASE_ID(x) setTCid(x)
#define SET_TEST_CASE_BRIEF(x) setTCbrief(x)

#define BEFORE(TC) int32_t TC::before()
#define AFTER(TC) int32_t TC::after()

#define BEFORE_TC(TC) int32_t TC::beforeTC() /*!< Use to declare your beforeTC function */
#define AFTER_TC(TC) int32_t TC::afterTC() /*!< Use to declare your afterTC function */

#define TEST_CASE_METHODS \
int32_t setup(); \
int32_t beforeTC(); \
int32_t afterTC(); \
int32_t before(); \
int32_t after(); /*!< Contains all methods that a Test must implement */

#endif //SE2_TEST_FRAMEWORK_TESTFRAMEWORK_H
