/*
 * SignalDistributer.cpp
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#include "SignalDistributer.h"
#include "CodeDefinition.h"
#include "Logger.h"
#include "Logscope.h"
#include "PuckManager.h"

SignalDistributer::SignalDistributer(PuckManager *puckManager, SortingSwichtControl *ssCntrl, ActorHandler *actorHandler):
	 puckManager_(puckManager)
	,ssCntrl_(ssCntrl)
	,actorHandler_(actorHandler)
{}

SignalDistributer::~SignalDistributer() {}

using namespace CodeDefinition;

void SignalDistributer::process(rcv::msg_t msg){
	HeightMeasurement::signal_t height_;
	PuckSignal::TimerSignal timer;

	LOG_SCOPE;

	switch(msg.code){
		case ISR :
			interrupt((interrupts::interruptSignals)msg.value);
			break;
		case SER_IN :
			serial((Serial_n::ser_proto_msg)msg.value);
			break;
		case TRANSM_IN :
			//puckManager_->deserialize() TODO FIX THE SERIALIZATION
			LOG_DEBUG << "[SignalDistributer] Transm_in not implemented \n";
			break;
		case PUCK_TIMER :
			timer.value = msg.value;
			timerForPuck(timer);
			break;
		case HEIGHT_MEASUREMENT :
			height_.value = msg.value;
			height(height_);
			break;
		case SORTING_SWITCH:
			ssCntrl_->close();
			break;
	}
}
using namespace interrupts;
void SignalDistributer::interrupt(interrupts::interruptSignals signal){
	LOG_SCOPE;
	PuckSignal::Signal m_sig;
	PuckManager::ManagerReturn mng_r;
	m_sig.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	m_sig.interruptSignal = (interrupts::interruptSignals) signal;
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
			mng_r = puckManager_->process(m_sig);
			DEBUG_MNG_RE(mng_r)
			actorHandler_->demultiplex(mng_r);
			break;
			//TODO give the buttons to the error handle
	}
}

void SignalDistributer::height(HeightMeasurement::signal_t signal){
	LOG_SCOPE;
	PuckManager::ManagerReturn mng_r;
	PuckSignal::Signal m_sig;
	m_sig.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	m_sig.heightSignal = signal;
	mng_r = puckManager_->process(m_sig);
	DEBUG_MNG_RE(mng_r)
	actorHandler_->demultiplex(mng_r);
}

void SignalDistributer::timerForPuck(PuckSignal::TimerSignal signal){
	LOG_SCOPE;
	PuckManager::ManagerReturn mng_r;
	PuckSignal::Signal m_sig;
	m_sig.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	m_sig.timerSignal = signal;
	mng_r = puckManager_->process(m_sig);
	DEBUG_MNG_RE(mng_r)
	actorHandler_->demultiplex(mng_r);
}


void SignalDistributer::serial(Serial_n::ser_proto_msg){
	//TODO Implement
}
