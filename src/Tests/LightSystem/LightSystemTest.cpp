/*
 * LightSystemTest.cpp
 *
 *  Created on: 11.05.2017
 *      @author: Matthis Keppner
 *
 */
#include "LightSystemTest.h"

using namespace HAL;
using namespace std;

SETUP(LightSystemTest){
    REG_TEST(test1, 1, "Test operation");
    REG_TEST(test2, 2, "Test LightSystemController");
    REG_TEST(test3, 3, "Test LightSystemHal");
    return 1;
};

BEFORE_TC(LightSystemTest){
    return 1;
};

AFTER_TC(LightSystemTest){
    return 1;
};

BEFORE(LightSystemTest){
	int chid = ChannelCreate_r(0);
	if(chid < 0){
		LOG_ERROR << "Channel Create failed" << endl;
		return 0;
	}

	// Request priviledges for the current thread to access hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		LOG_DEBUG << "Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

	boundary = new LightSystemHal();
	controller = new LightSystemController(chid, boundary);
	lightSystem = new LightSystemService(chid);
    return 1;
};

AFTER(LightSystemTest){
	LOG_DEBUG << "Cleanup the mess" << std::endl;
	delete lightSystem;
	LOG_DEBUG << "lightSystem deleted" << std::endl;
	delete controller;
	LOG_DEBUG << "controller deleted" << std::endl;
	delete boundary;
	LOG_DEBUG << "boundary deleted" << std::endl;
    return 1;
};

TEST_IMPL(LightSystemTest, test1){
	LOG_SCOPE;

	Level warning = OPERATING;
    LOG_DEBUG << "Set Warning Level: " << warning << endl;

	lightSystem->setWarningLevel(warning);
	this_thread::sleep_for(chrono::seconds(1));

	return TEST_PASSED;
}

TEST_IMPL(LightSystemTest, test2) {
	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	// Set different warning levels
	/* FIXME: Cardinality of enum instead of last definition plus 1 */
	for ( int warning = OPERATING; warning < CLEAR_ALL+1; warning++ )
	{
		LOG_DEBUG << "Set Warning Level: " << warning << endl;
		lightSystem->setWarningLevel((Level) warning);
		this_thread::sleep_for(chrono::seconds(PAUSE_TIME));
	}
	return TEST_PASSED;
}


TEST_IMPL(LightSystemTest, test3) {
	LOG_SCOPE;

	for (int i = 0; i<10; i++) {
		boundary->lightOn(RED);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		boundary->lightOn(YELLOW);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		boundary->lightOn(GREEN);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		boundary->lightOff(RED);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		boundary->lightOff(YELLOW);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		boundary->lightOff(GREEN);
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return TEST_PASSED;
}
