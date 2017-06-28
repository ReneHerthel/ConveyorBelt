/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    error_handler
 * @{
 *
 * @brief      Function declaration of the ErrorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ErrorHandler.h"

#include "DistanceObservable.h"
#include "DistanceEnum.h"
#include "Signals.h"
#include "CodeDefinition.h"
#include "SerialProtocoll.h"
#include "Signals.h"

#include <iostream>
using namespace std;
using namespace HAL;

ErrorHandler::ErrorHandler( int chid,
                            ConveyorBeltService *conveyorBeltService,
                            LightSystemService *lightSystemService,
                            SerialService *serialService,
                            PuckManager *puckManager)
    :    m_hasError(false)
    ,    m_resetPressed(false)
    ,    m_conveyorBeltService(conveyorBeltService)
    ,    m_lightSystemService(lightSystemService)
	, 	 m_serialService(serialService)
	, 	 m_puckManager(puckManager)
{
    m_lightSystemService->setWarningLevel(Level::OPERATING);
}

ErrorHandler::~ErrorHandler()
{
    // Nothing todo so far.
}

void ErrorHandler::process(PuckManager::ManagerReturn &manager)
{
	LOG_DEBUG << "[ErrorHandler] Demux Manager return \n";
	LOG_DEBUG << "[ErrorHandler] Actor Flag " << manager.actorFlag << " actorSignal " << (int)manager.actorSignal << "\n";

	//if slide full return a warning
	if (manager.actorFlag && manager.actorSignal == PuckManager::ActorSignal::SEND_SLIDE_FULL){
		 m_lightSystemService->setWarningLevel(Level::WARNING_OCCURED);
		 LOG_DEBUG << "[ErrorHandler] Slide is full \n";
	}
	if (manager.actorFlag && manager.actorSignal == PuckManager::ActorSignal::SEND_SLIDE_EMPTY){
		 m_lightSystemService->setWarningLevel(Level::CLEAR_WARNING);
		 m_lightSystemService->setWarningLevel(Level::OPERATING);
		 LOG_DEBUG << "[ErrorHandler] Slide is empty \n";
	}

	//Only handle when error code
    if (manager.errorFlag) {
		m_hasError = true;

		m_lightSystemService->setWarningLevel(Level::ERROR_OCCURED);

		DistanceObservable &distO = DistanceObservable::getInstance();
		distO.updateSpeed(DistanceSpeed::STOP);

		m_conveyorBeltService->changeState(ConveyorBeltState::STOP);
		m_serialService->sendMsg(Serial_n::ser_proto_msg::STOP_SER);

		switch (manager.errorSignal) {

			case PuckManager::ErrorSignal::PUCK_LOST:
				cout << "[ErrorHandler] PUCK_LOST - Late Timer" << endl;
				LOG_DEBUG << "[ErrorHandler] PUCK_LOST - Late Timer" << endl;
				break;

			case PuckManager::ErrorSignal::PUCK_MOVED:
				cout << "[ErrorHandler] PUCK_MOVED - Puck triggered light barrier before early timer" << endl;
				LOG_DEBUG << "[ErrorHandler] PUCK_MOVED - Puck triggered light barrier before early timer" << endl;
				break;

			case PuckManager::ErrorSignal::UNEXPECTED_SIGNAL:
				cout << "[ErrorHandler] UNEXPECTED_SIGNAL - Signal could not be processed" << endl;
				LOG_DEBUG << "[ErrorHandler] UNEXPECTED_SIGNAL - Signal could not be processed" << endl;
				break;

			case PuckManager::ErrorSignal::MULTIPLE_ACCEPT:
				cout << "[ErrorHandler] MULTIPLE_ACCEPT - Shouldn't happen - multiple pucks were triggered" << endl;
				LOG_DEBUG << "[ErrorHandler] MULTIPLE_ACCEPT - Shouldn't happen - multiple pucks were triggered" << endl;
				break;

			case PuckManager::ErrorSignal::MULTIPLE_WARNING:
				cout << "[ErrorHandler] MULTIPLE_WARNING" << endl;
				LOG_DEBUG << "[ErrorHandler] MULTIPLE_WARNING" << endl;
				break;

			case PuckManager::ErrorSignal::BOTH_SLIDES_FULL:
				 cout << "[ErrorHandler] BOTH_SLIDES_FULL" << endl;
				 LOG_DEBUG << "[ErrorHandler] BOTH_SLIDES_FULL" << endl;
				 m_puckManager->reset();
				 break;

			default:
				 LOG_DEBUG << "[ErrorHandler] Unkown Error !!!" << endl;
				break;
		}
    }
}


bool ErrorHandler::hasError()
{
	LOG_DEBUG << "[ErrorHandler] Error: " << m_hasError << "\n";
    return m_hasError;
}

void ErrorHandler::handleEvent(rcv::msg_t event)
{
	LOG_DEBUG << "[ErrorHandler] Trying to demux " << event.code << " " << event.value << "\n";
	switch(event.code){
		case CodeDefinition::SER_IN :
			if( event.value == Serial_n::ser_proto_msg::ESTOP_SER ||
				event.value == Serial_n::ser_proto_msg::ERROR_SER ||
				event.value == Serial_n::ser_proto_msg::NO_CON_SER  ){
				LOG_DEBUG << "[ErrorHandler] Got error from serial \n";
				m_lightSystemService->setWarningLevel(Level::ERROR_OCCURED);
				m_conveyorBeltService->changeState(ConveyorBeltState::STOP);
				m_hasError = true;
				m_resetPressed = false;
			}
			break;
		case CodeDefinition::ISR :
			if(event.value == interrupts::BUTTON_ESTOP_IN){
				LOG_DEBUG << "[ErrorHandler] Got Estop from ISR \n";
				m_lightSystemService->setWarningLevel(Level::ERROR_OCCURED);
				m_serialService->sendMsg(Serial_n::ser_proto_msg::ESTOP_SER);
				m_conveyorBeltService->changeState(ConveyorBeltState::STOP);
				m_hasError = true;
				m_resetPressed = false;
			}
			break;
		default :
			//Nothing to do
			break;
	}

	if(m_hasError){
		 	bool buttonReset = false;
		    bool buttonStart = false;

		    if (event.code == 5) { // 5 is hardcoded in the ISR. TODO Serial signal needs to get through when error is acknowledged on other machine
		    	switch(event.value) {

					case interrupts::BUTTON_RESET:
						buttonReset = true;
						break;

					case interrupts::BUTTON_START:
						buttonStart = true;
						break;

					case interrupts::SLIDE_OUT:
						LOG_DEBUG << "[ErrorHandler] Handling SLIDE_OUT error event " << endl;
						PuckSignal::Signal signal;
						signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
						signal.interruptSignal = (interrupts::interruptSignals) event.value;
						m_puckManager->process(signal);
						m_serialService->sendMsg(Serial_n::ser_proto_msg::SLIDE_EMTPY_SER); //huge bawrf
						break;
					default:
						// Nothing todo so far.
						break;
				}
		    } else if(event.code == CodeDefinition::Code::SER_IN) {
		    	if(event.value == Serial_n::ser_proto_msg::SLIDE_EMTPY_SER){
		    		PuckSignal::Signal signal;
					signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
					signal.serialSignal = (Serial_n::ser_proto_msg) event.value;
					m_puckManager->process(signal);
		    	}
		    }

		    LOG_DEBUG << "[ErrorHandler] Trying to handle error event " << int(event.value) << endl;


		    if (buttonReset && m_hasError) {
		        m_resetPressed = true;
		        cout << "Error acknowledged" << endl;
		        m_lightSystemService->setWarningLevel(Level::ERROR_ACKNOWLEDGED);
		    } else if (buttonStart && m_resetPressed && m_hasError) { // Only go further when reset was pressed before.
		    	m_puckManager->resetPucks();
				cout << "Clear error" << endl;
				m_lightSystemService->setWarningLevel(Level::OPERATING);
				m_resetPressed = false;
				m_hasError = false;
		    }
	}
}

/** @} */
