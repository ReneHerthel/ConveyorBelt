/*
 * SignalDistributer.h
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#ifndef SIGNALDISTRIBUTER_H_
#define SIGNALDISTRIBUTER_H_

#include "PuckManager.h"
#include "PulseMessageReceiverService.h"
#include "SortingSwichtControl.h"
#include "Signal.h"
#include "SerialProtocoll.h"
#include "HeightSignal.h"
#include "PuckContext.h"
#include "ActorHandler.h"

//include the error handler

#define DEBUG_MNG_RE(mr) \
				switch(mr.errorSignal){ 									\
						case PuckManager::ErrorSignal::PUCK_LOST:			\
							std::cout << "PUCK_LOST - Late Timer \n";		\
							break;											\
						case PuckManager::ErrorSignal::PUCK_MOVED:			\
							std::cout << "PUCK_MOVED - Puck triggered light barrier before early timer \n"; \
							break;																			\
						case PuckManager::ErrorSignal::UNEXPECTED_SIGNAL:									\
							std::cout << "UNEXPECTED_SIGNAL - Signal could not be processed \n";			\
							break;																			\
						case PuckManager::ErrorSignal::MULTIPLE_ACCEPT:										\
							std::cout << "MULTIPLE_ACCEPT - Shouldn't happen - multiple pucks were triggered \n"; \
							break;											\
						case PuckManager::ErrorSignal::MULTIPLE_WARNING:	\
							std::cout << "MULTIPLE_WARNING \n";				\
							break;											\
				}

class SignalDistributer {
public:
	SignalDistributer(PuckManager *puckManager, SortingSwichtControl *ssCntrl, ActorHandler *actorHandler); //TODO add error handler
	virtual ~SignalDistributer();

	void process(rcv::msg_t msg);

private:
	void interrupt(interrupts::interruptSignals signal);
	void height(HeightMeasurement::signal_t signal);
	void serial(Serial_n::ser_proto_msg signal);
	void timerForPuck(PuckSignal::TimerSignal signal);

	PuckManager *puckManager_;
	SortingSwichtControl *ssCntrl_;
	ActorHandler *actorHandler_;
};

#endif /* SIGNALDISTRIBUTER_H_ */
