/*
 * LightSystemTest.h
 *
 *  Created on: 11.05.2017
 *      Author: aca592
 */

#ifndef LIGHTSYSTEMTEST_H_
#define LIGHTSYSTEMTEST_H_

#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "LightSystemEnum.h"
#include "LightSystemController.h"
#include "LightSystemHal.h"
#include "LightSystemService.h"
#include "TestCase.h"
#include "TestFramework.h"

#include <iostream>

#define PAUSE_TIME 10
#define LS_MODULE_ID 4
#define PORTA_ADDR 0x300
#define GREEN_SHIFT		5
#define YELLOW_SHIFT	6
#define RED_SHIFT		7
#define ALL_SHIFT		(GREEN_SHIFT | YELLOW_SHIFT | RED_SHIFT)


class LightSystemTest : public TestCase{
public:
    LightSystemTest(int id, std::string brief): TestCase(id, brief){};
protected:
    TEST(test1);

protected:
    TEST_CASE_METHODS
};

#endif /* LIGHTSYSTEMTEST_H_ */
