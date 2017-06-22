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
#include "LightSystemHal.h"
#include "LightSystemController.h"
#include "BLightSystem.h"

#include "PuckManager.h"
#include "PuckSignal.h"

#include "LightSystemEnum.h"

#include "HeightMeasurementController.h"
#include "HeightService.h"

#include "ActorHandler.h"

#include "SignalDistributer.h"
#include "SortingSwichtControl.h"

SETUP(MachineOne){
	REG_TEST(programm_m1, 1, "Just Create some distance trackers an let them run (no changes on the way)");
};

BEFORE_TC(MachineOne){return 1;}

AFTER_TC(MachineOne){return 1;}

BEFORE(MachineOne){return 1;}

AFTER(MachineOne){return 1;}

TEST_IMPL(MachineOne, programm_m1){

	//----------INIT------------

	//INIT MAIN CHANNEL
	PulseMessageReceiverService mainChannel; ///Main communication channel
	int mainChid = mainChannel.newChannel(); ///Chid of main com

	//INIT ISR
	Control isrCntrl(mainChid);
	ISR isr(&isrCntrl);
	std::thread isr_th(ref(isr));


	//INIT Serial
	//Init PMR
	rcv::PulseMessageReceiverService pmrSer1;
	int pmrSer1Chid = pmrSer1.newChannel();

	//Init PMS
	rcv::PulseMessageReceiverService pmsChannelCreatorSer1;
	int pmsSer1Chid = pmsChannelCreatorSer1.newChannel();
	PulseMessageSenderService pmsSer1(pmsSer1Chid);

	//Init Sender & Receiver
	char ser1_path[] = "/dev/ser1";
	SerialSender senderSer1(ser1_path);
	SerialReceiver receiverSer1(ser1_path);

	//Init Protocol
	SerialProtocoll protoSer1(SENDER);

	//Init Serial
	Serial ser1(receiverSer1, senderSer1, protoSer1, pmsSer1Chid, pmrSer1Chid);


	//Init SerialService
	SerialService serialService(pmsSer1Chid);


	//INIT CBS
	ConveyorBeltService cbs;

	//INIT CALIBRATION AND CALIBRATE
	Calibration& calibration = Calibration::getInstance();
	std::cout << "start Hightcal" << "\n";
	cout.flush();
	//calibration.calibrateHeighMeasurement();
	std::cout << "start distancecal" << "\n";
	cout.flush();
	calibration.loadFromDisk("/Calibration.dat");

	//INIT LIGHTSYSTEM
	/*PulseMessageReceiverService lightsystemChannel; ///Lightsystem cntrl channel
	int lightsystemChid = ChannelCreate_r(0); //lightsystemChannel.newChannel();

	std::cout << "LightSystemChid" <<lightsystemChid << "\n";
	cout.flush();
	BLightSystem *lsHal = new LightSystemHal();
	LightSystemController *lightSystemCntrl = new LightSystemController(lightsystemChid, lsHal);
	LightSystemService *lightSystem = new LightSystemService(lightsystemChid);
	lightSystem->setWarningLevel(WARNING_OCCURED);*/

	//INIT HEIGHTMEASUREMENT
	PulseMessageReceiverService heightMChannelCreator; ///Create channel for heightm
	int heightMChid = heightMChannelCreator.newChannel();
	HeightMeasurementController::CalibrationData calData = calibration.getHmCalibration();
	HeightMeasurementController hmController(heightMChid, mainChid, &calData);
	HeightService heightService(heightMChid);

	//INIT SWITCH CONTROL
	SortingSwichtControl ssCntrl(mainChid);

	//Init actor handler
	ActorHandler actorHandler(cbs, heightService, ssCntrl, serialService);

	//INIT PUCK MNG
	PuckManager puckManager(mainChid);

	//INIT SIGNAL DISTRIBUTER
	SignalDistributer signalDistributer(&puckManager, &ssCntrl, &actorHandler);

	//TESTLOOP
	rcv::msg_t event;

	while(1){
		event = mainChannel.receivePulseMessage();
		std::cout << "Got something \n";
		switch(event.code){
			case 0: std::cout << "\n\n Height \n"; break; //Height
			case 2: std::cout << "\n\n Serial \n";break; //Serial
			case 4: std::cout << "\n\n Serial \n";break; //Serial
			case 5: std::cout << "\n\n ISR \n";break; //ISR
		}
		cout.flush();


		if(event.value == interrupts::BUTTON_RESET){
			cbs.changeState(ConveyorBeltState::STOP);
			std::cout << "\n\n RESET \n";
			puckManager = PuckManager(mainChid);
		}

		signalDistributer.process(event);
	}

}



