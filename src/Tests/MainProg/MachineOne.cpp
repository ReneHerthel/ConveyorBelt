//
// Created by Silt on 23.04.2017.
//

#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "MachineOne.h"
#include "logger.h"

#include "ISR.h"
#include "Control.h"

#include "PulseMessageReceiverService.h"

#include "LightSystemService.h"

SETUP(MachineOne){
	REG_TEST(Calibrate, 1, "Just Create some distance trackers an let them run (no changes on the way)");
};

BEFORE_TC(MachineOne){return 1;}

AFTER_TC(MachineOne){return 1;}

BEFORE(MachineOne){return 1;}

AFTER(MachineOne){return 1;}

TEST_IMPL(MachineOne, Calibrate){

	//----------INIT------------

	//INIT MAIN CHANNEL
	PulseMessageReceiverService mainChannel; ///Main communication channel
	int mainChannelChid = mainChannel.newChannel(); ///Chid of main com

	//INIT ISR
	Control isrCntrl(mainCom);
	ISR isr(isrCntrl);

	//INIT LIGHTSYSTEM

}



