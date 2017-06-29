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

#include "ErrorHandler.h"

#include <thread>
#include <chrono>

#include "EmbeddedRecorder.h"
#include "EmbeddedRecorderSignals.h"

#include "CodeDefinition.h"

using namespace HAL;

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
	Serial ser1(receiverSer1, senderSer1, protoSer1, pmsSer1Chid, mainChid);


	//Init SerialService
	SerialService serialService(pmsSer1Chid);

	std::thread ser1_thread(ref(ser1));


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

	LightSystemHal * lhal = new LightSystemHal();
	LightSystemService * lservice = new LightSystemService(mainChid);
	LightSystemController * lcontrol = new LightSystemController(mainChid, lhal);

	ErrorHandler errorHandler(mainChid, cbs, lservice);

	//INIT SIGNAL DISTRIBUTER
	SignalDistributer signalDistributer(&puckManager, &ssCntrl, &actorHandler, &errorHandler);

	//TESTLOOP
	rcv::msg_t event;

	rec::EmbeddedRecorder * embeddedRecorder = new rec::EmbeddedRecorder(mainChid);

	bool isPlaying = false; // NOTE: this is to dirty. D how to fix.

	while(1) {

		event = mainChannel.receivePulseMessage();
		std::cout << "[MachineOne] " << event.code << " | " << event.value << std::endl;

		if (!isPlaying) {
			/*
			 * NOTE: DO NOT RECORD PUCK TIMER! Or they will be more than one for a single puck.
			 * NOTE: DO NOT RECORD THE RESET BUTTON! Or you will have a suuhuuper loop!
			 */
			if (event.code != 25 || (event.code == 5 && event.value != 16384)) {
                embeddedRecorder->writeMessageIntoBuffer(event);
        		embeddedRecorder->saveRecordedData();
			}
		}

		if (event.code == CodeDefinition::Code::EMBEDDED_RECORDER) {
			if (event.value == rec::Signals::RECORD_PLAY) {
				std::cout << "PLAY NOW" << std::endl;
			}

			if (event.value == rec::Signals::RECORD_STOP){
				std::cout << "STOP NOW" << std::endl;
			}
		}

		if(event.value == interrupts::BUTTON_RESET){
			std::cout << "\n\n RESET \n";

			if(!isPlaying){
				isPlaying = true;
				cbs.changeState(ConveyorBeltState::STOP);
				puckManager = PuckManager(mainChid);
				embeddedRecorder->showRecordedData();
				embeddedRecorder->newBuffer();
				embeddedRecorder->loadRecordedData();
				embeddedRecorder->playRecordedData();
			}
		}

		if (event.code != CodeDefinition::Code::EMBEDDED_RECORDER || event.code != CodeDefinition::Code::EMBEDDED_RECORDER) {
			signalDistributer.process(event);
		}
	}

}



