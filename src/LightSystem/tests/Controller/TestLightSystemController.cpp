/*
 * TestLightSystemController.cpp : Test dependency injection and setter
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include "TestLightSystemController.h"

using namespace HAL;
using namespace std;

int main(int argc, char *argv[]) {
	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	int chid = ChannelCreate_r(0);
	if(chid < 0){
		LOG_ERROR << "Channel Create failed" << endl;
	}

    int coid = ConnectAttach_r(ND_LOCAL_NODE,0,chid,0,0);
    if(coid < 0) {
    	LOG_ERROR << "Channel Attach failed" << endl;
    }

    LightSystemHal boundary = LightSystemHal();
    LightSystemController controller = LightSystemController(chid, &boundary);
    LightSystemService lightSystem = LightSystemService(chid);
     

    // Set different warning levels
    /* FIXME: Cardinality of enum instead of last definition plus 1 */
    for ( int warning = OPERATING; warning < CLEAR_ALL+1; warning++ )
    {
        LOG_DEBUG << "Set Warning Level: " << warning << endl;
        lightSystem.setWarningLevel((Level) warning);
        this_thread::sleep_for(chrono::seconds(PAUSE_TIME));
    }
}
