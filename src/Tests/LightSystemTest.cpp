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
	std::cout << "Start Lightsystem Test"<< std::endl;
	// Request priviledges for the current thread to access hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Create Channels"<< std::endl;
	int chid = ChannelCreate_r(0);
	if(chid < 0){
            std::cout << "Channel Create failed" << endl;
	}
	std::cout << "Objects"<< std::endl;

	LightSystemHal* boundary = new LightSystemHal();
	LightSystemController* controller = new LightSystemController(chid, boundary);
	LightSystemService* lightSystem = new LightSystemService(chid);
	std::cout << "Objects created"<< std::endl;

	unsigned char port_value = 0;
	Level warning = OPERATING;
        std::cout << "Set Warning Level: " << warning << endl;

	std::cout << "The real test"<< std::endl;
	lightSystem->setWarningLevel(warning);
	this_thread::sleep_for(chrono::seconds(1));
	port_value = in8(PORTA_ADDR);

        std::cout << "Cleanup the mess" << std::endl;
        delete lightSystem;
        delete controller;
        delete boundary;

        std::cout << "Return Result" << std::endl;
	if((port_value & (1 << GREEN_SHIFT))){ // checks if greenLED  is on.
		std::cout << "Passed" << std::endl;
		return TEST_PASSED;
	} else {
		std::cout << "Failed"<< std::endl;
		return TEST_FAILED;
	}
}


