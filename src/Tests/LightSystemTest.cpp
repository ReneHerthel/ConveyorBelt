/*
 * LightSystemTest.cpp
 *
 *  Created on: 11.05.2017
 *      @author: Matthis Keppner
 *
 */
#include "LightSystemTest.h"

SETUP(LightSystemTest){
    REG_TEST(test1, 1, "Test1 Brief");
};

BEFORE_TC(LightSystemTest){

    return 1;
};

AFTER_TC(LightSystemTest){
	std::cout << "Der TestCase ist fertig" <<std::endl;
    return 1;
};

BEFORE(LightSystemTest){
    return 1;
};

AFTER(LightSystemTest){
    return 1;
};

TEST_IMPL(LightSystemTest, test1){
	// Request priviledges for the current thread to access hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}
	//LOG_SCOPE;
	//LOG_SET_LEVEL(DEBUG);

	int chid = ChannelCreate_r(0);
	if(chid < 0){
		//LOG_ERROR << "Channel Create failed" << endl;
	}
		LightSystemHal boundary = LightSystemHal();
		LightSystemController controller = LightSystemController(chid, &boundary);
		LightSystemService lightSystem = LightSystemService(chid);

	unsigned char port_value = 0;
	Level warning = OPERATING;
	//LOG_DEBUG << "Set Warning Level: " << warning << endl;
	lightSystem.setWarningLevel( warning);
	this_thread::sleep_for(chrono::seconds(PAUSE_TIME));
	port_value = in8(PORTA_ADDR);
	if((port_value & (1 << GREEN_SHIFT))){ // checks if greenLED  is on.
		return PASSED;
	}
		return FAILED;
}


