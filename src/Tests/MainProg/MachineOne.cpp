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
#include "PulseMessageSenderService.h"

#include "Calibration.h"

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
	int mainChid = mainChannel.newChannel(); ///Chid of main com

	//INIT ISR
	Control isrCntrl(mainChid);
	ISR isr(isrCntrl);

	//INIT LIGHTSYSTEM
	PulseMessageReceiverService lightsystemChannel; ///Lightsystem cntrl channel
	int lightsystemChid = lightsystemChannel.newChannel();

	LightSystemHal lsHal();
	LightSystemController lightSystemCntrl(lightsystemChid, lsHal);
	LightSystemService lightSystem(lightsystemChid);

	//INIT CALIBRATION AND CALIBRATE
	Calibration& calibration = Calibration::getInstance();
	calibration.calibrateHeighMeasurement();
	calibration.calibrate();

	//INIT HEIGHTMEASUREMENT
	PulseMessageReceiverService heightMChannelCreator; ///Create channel for heightm
	int heightMChid = heightMChannelCreator.newChannel();
	PulseMessageSenderService heightMChannel(heightMChid);

	HeightMeasurementService service(heightMChid, mainChannelChid, calibration.getHmCalibration());



}



