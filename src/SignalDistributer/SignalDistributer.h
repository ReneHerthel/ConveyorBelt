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

//include the error handler

class SignalDistributer {
public:
	SignalDistributer(PuckManager *puckManager, SortingSwichtControl *ssCntrl); //TODO add error handler
	virtual ~SignalDistributer();

	void process(rcv::msg_t msg);

	void interrupt(interrupts::interruptSignals signal);
	void height(HeightMeasurement::signal_t signal);
	void serial(Serial_n::ser_proto_msg);
	void timerForPuck();
	void timerForSwitch();

private:
	PuckManager *puckManager_;
	SortingSwichtControl *ssCntrl_;
};

#endif /* SIGNALDISTRIBUTER_H_ */
