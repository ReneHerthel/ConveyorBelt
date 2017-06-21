/*
 * SignalDistributer.cpp
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#include "SignalDistributer.h"
#include "CodeDefinition.h"
#include "Logger.h"

SignalDistributer::SignalDistributer(PuckManager *puckManager, SortingSwichtControl *ssCntrl):
	 puckManager_(puckManager)
	,ssCntrl_(ssCntrl_)
{}

SignalDistributer::~SignalDistributer() {}

using namespace CodeDefinition;

void SignalDistributer::process(rcv::msg_t msg){
	switch(msg.code){
		case ISR :
			interrupt((interrupts::interruptSignals)msg.value);
			break;
		case SER_IN :
			serial((Serial_n::ser_proto_msg)msg.value);
			break;
		case TRANSM_IN :
			//puckManager_->deserialize() TODO FIX THE SERIALIZATION
			LOG_ERROR << "[SignalDistributer] Transm_in not implemented \n";
			break;
		case PUCK_TIMER :
			timerForPuck({.value = msg.value}); //Ewww
			break;
		case HEIGHT_MEASUREMENT :
			height({.value = msg.value});
			break;
		case SORTING_SWITCH:
			ssCntrl_->close();
			break;
	}
}
using namespace interrupts;
void SignalDistributer::interrupt(interrupts::interruptSignals signal){
	PuckSignal::Signal m_sig;
	m_sig.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	m_sig.interruptSignal = signal;
	switch(signal){
		case INLET_IN	 		  :
		case INLET_OUT	 		  :
		case HEIGHTMEASUREMENT_IN :
		case HEIGHTMEASUREMENT_OUT:
		case SWITCH_IN	 		  :
		case METAL_DETECT	 	  :
		case SWITCH_OPEN	 	  :
		case SLIDE_IN	 		  :
		case SLIDE_OUT	 		  :
		case OUTLET_IN	 		  :
		case OUTLET_OUT           :
			puckManager_->process(m_sig);
			break;
			//TODO give the buttons to the error handle
	}
}

void SignalDistributer::height(HeightMeasurement::signal_t signal){
	PuckSignal::Signal m_sig;
	m_sig.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	m_sig.heightSignal = signal;
	puckManager_->process(m_sig);
}

void SignalDistributer::serial(Serial_n::ser_proto_msg){
	//TODO Implement
}

