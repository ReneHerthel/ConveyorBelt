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
#include "Signals.h"

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

#include "ConveyorBeltService.h"
#include "ConveyorBeltState.h"

#include "SortingSwichtControl.h"

#include "DistanceObservable.h"
#include "DistanceEnum.h"

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

	//Init CBS
	ConveyorBeltService cbs;

	//INIT ISR
	Control isrCntrl(mainChid);
	ISR isr(&isrCntrl);
	std::thread isr_th(ref(isr));

	//INIT ISR
	Control isrCntrl(mainChid);
	ISR isr(&isrCntrl);
	std::thread isr_th(ref(isr));

	//INIT CALIBRATION AND CALIBRATE
	Calibration& calibration = Calibration::getInstance();
	std::cout << "start Hightcal" << "\n";
	cout.flush();
	calibration.calibrateHeighMeasurement();
	std::cout << "start distancecal" << "\n";
		cout.flush();
	calibration.calibrate(mainChid);

	//INIT DistancObs
	DistanceObservable &distO = DistanceObservable::getInstance();
/*
	//INIT LIGHTSYSTEM
	PulseMessageReceiverService lightsystemChannel; ///Lightsystem cntrl channel
	int lightsystemChid = ChannelCreate_r(0); //lightsystemChannel.newChannel();

	std::cout << "LightSystemChid" <<lightsystemChid << "\n";
	cout.flush();
	BLightSystem *lsHal = new LightSystemHal();
	LightSystemController *lightSystemCntrl = new LightSystemController(lightsystemChid, lsHal);
	LightSystemService *lightSystem = new LightSystemService(lightsystemChid);
	lightSystem->setWarningLevel(WARNING_OCCURED);
*/
	//INIT HEIGHTMEASUREMENT
	//PulseMessageReceiverService heightMChannelCreator; ///Create channel for heightm
	//int heightMChid = heightMChannelCreator.newChannel();
	//PulseMessageSenderService heightMChannel(heightMChid);

	//HeightMeasurementService::CalibrationData calData = calibration.getHmCalibration();

	//HeightMeasurementService hmservice(heightMChid, mainChid, &calData);

	//INIT PUCK MNG
	PuckManager *puckManager = new PuckManager(mainChid);

	//INIT Switch Cntrl
	SortingSwichtControl sswitchCntrl(mainChid);

	//TESTLOOP
	rcv::msg_t event;
	PuckManager::ManagerReturn mr;
	PuckSignal::Signal m_sig;
	while(1){
		event = mainChannel.receivePulseMessage();
		std::cout << "Got something \n";
		switch(event.code){
			case 0: std::cout << "\n\n Height \n";
				m_sig.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
				m_sig.heightSignal.value = event.value;
				mr = puckManager->process(m_sig);
				break; //Height
			case 2: std::cout << "\n\n Serial \n";break; //Serial
			case 4: std::cout << "\n\n Serial \n";break; //Serial
			case 5:
				if(event.value == interrupts::BUTTON_RESET){
					delete puckManager;
					puckManager = new PuckManager(mainChid);
				} else {
					m_sig.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
					m_sig.interruptSignal = (interrupts::interruptSignals) event.value;
					mr = puckManager->process(m_sig);
				}
				break;

			case 25:
				m_sig.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
				m_sig.timerSignal.value = event.value;
				mr = puckManager->process(m_sig);
				break;
			case 19:
				sswitchCntrl.close();
				break;

		}

		if(mr.errorFlag){
			cbs.changeState(ConveyorBeltState::STOP);
		}
		else{
		std::cout << "ManagerReturn " << mr.actorFlag << "\n" << mr.errorFlag << "\n";
		cout.flush();
		switch(mr.speedSignal){
			case PuckSignal::PuckSpeed::STOP:
				cbs.changeState(ConveyorBeltState::STOP);
				distO.updateSpeed(DistanceSpeed::STOP);
				break;
			case PuckSignal::PuckSpeed::SLOW:
				cbs.changeState(ConveyorBeltState::RIGHTSLOW);
				distO.updateSpeed(DistanceSpeed::SLOW);
				break;
			case PuckSignal::PuckSpeed::FAST:
				cbs.changeState(ConveyorBeltState::RIGHTFAST);
				distO.updateSpeed(DistanceSpeed::FAST);
				break;
		}
		}
		if(mr.actorFlag){
			switch(mr.actorSignal){
				case PuckManager::OPEN_SWITCH :
					sswitchCntrl.open();
					break;
			}
		}


		cout.flush();

	}

}



