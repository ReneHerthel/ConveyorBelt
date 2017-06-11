/*
 * PuckContext.cpp
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#include "PuckContext.h"

#include "Signals.h"
#include "Logger.h"
#include "LogScope.h"

#include <new>

PuckContext::PuckContext() {
	LOG_SCOPE;
#if !machine
	LOG_DEBUG << "Using machine0\n";
	statePtr = &inletState;
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
#else
	LOG_DEBUG << "Using machine1\n";
	statePtr = &transferState;
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//startTimers();
#endif
}

PuckSignal::Return PuckContext::process(PuckSignal::Signal signal) {
	LOG_SCOPE;
	switch(signal.signalType) {
		case PuckSignal::SignalType::HEIGHT_SIGNAL:
			LOG_DEBUG << "Signal is a height signal\n";
			statePtr->type();
			if(statePtr->returnValue.puckReturn == PuckSignal::PuckReturn::ACCEPT) {
				statePtr->puckType.heightType = signal.heightSignal;
			}
			break;

		case PuckSignal::SignalType::TIMER_SIGNAL:
			LOG_DEBUG << "Signal is a timer signal\n";
			switch(signal.timerSignal.type) {
				case PuckSignal::TimerType::EARLY_TIMER:
					LOG_DEBUG << "Signal is early timer\n";
					statePtr->earlyTimer();
					break;
				case PuckSignal::TimerType::LATE_TIMER:
					LOG_DEBUG << "Signal is late timer\n";
					statePtr->lateTimer();
					break;
				default:
					LOG_DEBUG << "Unknown signal\n";
			}
			break;

		case PuckSignal::SignalType::INTERRUPT_SIGNAL:
			LOG_DEBUG << "Signal is a interrupt signal\n";
			switch(signal.interruptSignal) {
				case interrupts::interruptSignals::INLET_IN:
					LOG_DEBUG << "Signal is inlet_in\n";
					statePtr->inletIn();
					break;
				case interrupts::interruptSignals::INLET_OUT:
					LOG_DEBUG << "Signal is inlet_out\n";
					statePtr->inletOut();
					break;
				case interrupts::interruptSignals::HEIGHTMEASUREMENT_IN:
					LOG_DEBUG << "Signal is heightmeasurement_in\n";
					statePtr->heightmeasurementIn();
					break;
				case interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT:
					LOG_DEBUG << "Signal is heightmeasurement_out\n";
					statePtr->heightmeasurementOut();
					break;
				case interrupts::interruptSignals::METAL_DETECT:
					LOG_DEBUG << "Signal is metal_detect\n";
					statePtr->metalDetect();
					break;
				case interrupts::interruptSignals::SWITCH_IN:
					LOG_DEBUG << "Signal is switch_in\n";
					statePtr->switchIn();
					break;
				case interrupts::interruptSignals::SWITCH_OPEN:
					LOG_DEBUG << "Signal is switch_open\n";
					statePtr->switchOpen();
					break;
				case interrupts::interruptSignals::SLIDE_IN:
					LOG_DEBUG << "Signal is slide_in\n";
					statePtr->slideIn();
					break;
				case interrupts::interruptSignals::SLIDE_OUT:
					LOG_DEBUG << "Signal is slide_out\n";
					statePtr->slideOut();
					break;
				case interrupts::interruptSignals::OUTLET_IN:
					LOG_DEBUG << "Signal is outlet_in\n";
					statePtr->outletIn();
					break;
				case interrupts::interruptSignals::OUTLET_OUT:
					LOG_DEBUG << "Signal is outlet_out\n";
					statePtr->outletOut();
					break;
				default:
					LOG_DEBUG << "Unknown signal\n";
			}
			break;

		case PuckSignal::SignalType::SERIAL_SIGNAL:
			LOG_DEBUG << "Signal is a serial signal\n";
			switch(signal.serialSignal) {
				case Serial_n::ser_proto_msg::ACCEPT_SER:
					LOG_DEBUG << "Signal is accept_ser\n";
					statePtr->serialAccept();
					break;
				case Serial_n::ser_proto_msg::STOP_SER:
					LOG_DEBUG << "Signal is stop_ser\n";
					statePtr->serialStop();
					break;
				case Serial_n::ser_proto_msg::RESUME_SER:
					LOG_DEBUG << "Signal is resume_ser\n";
					statePtr->serialResume();
					break;
				case Serial_n::ser_proto_msg::RECEIVED_SER:
					LOG_DEBUG << "Signal is received_ser\n";
					statePtr->serialReceived();
					break;
				default:
					LOG_DEBUG << "Unknown signal\n";
			}
			break;

		default:
			LOG_DEBUG << "Unknown signal\n";
	}

	return statePtr->returnValue;
}

/*******************************************
 * SuperState
 */
void PuckContext::PuckState::inletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::inletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::heightmeasurementIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::heightmeasurementOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::switchOpen() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::slideIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::slideOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::outletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::outletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::metalDetect() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::serialAccept() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialReceived() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialStop() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::lateTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ERROR;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
}
/*******************************************/

#if machine
/*******************************************
 * TransferArea
 */
void PuckContext::TransferArea::inletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[TransferArea]->[TransferArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
}

void PuckContext::TransferArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[TransferArea]->[TransferTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) TransferTimer;
}
/*******************************************/

/*******************************************
 * TransferTimer
 */
void PuckContext::TransferTimer::inletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[TransferTimer]->[Inlet]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) Inlet;
}
/*******************************************/
#endif

/*******************************************
 * Inlet
 */
void PuckContext::Inlet::inletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Inlet]->[InletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//startTimers();
	new (this) InletArea;
}
/*******************************************/

/*******************************************
 * InletArea
 */
void PuckContext::InletArea::heightmeasurementIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[InletArea]->[InletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::InletArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[InletArea]->[InletTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) InletTimer;
}
/*******************************************/

/*******************************************
 * InletTimer
 */
void PuckContext::InletTimer::heightmeasurementIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[InletTimer]->[Heightmeasurement]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::HEIGHT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) Heightmeasurement;
}
/*******************************************/

/*******************************************
 * Heightmeasurement
 */
void PuckContext::Heightmeasurement::heightmeasurementOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Heightmeasurement]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//startTimers();
	new (this) MeasurementArea;
}
void PuckContext::Heightmeasurement::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[Heightmeasurement]->[Heightmeasurement]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// todo: setType
}
/*******************************************/

/*******************************************
 * MeasurementArea
 */
void PuckContext::MeasurementArea::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[MeasurementArea]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::MeasurementArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[MeasurementArea]->[MeasurementTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) MeasurementTimer;
}

void PuckContext::MeasurementArea::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[MeasurementArea]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}
/*******************************************/

/*******************************************
 * MeasurementTimer
 */
void PuckContext::MeasurementTimer::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[MeasurementTimer]->[TypeKnown]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) TypeKnown;
}

void PuckContext::MeasurementTimer::metalDetect() {
	LOG_SCOPE;
	LOG_DEBUG << "[MeasurementTimer]->[MetalType]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	puckType.metal = 1;
	new (this) MetalType;
}
/*******************************************/

/*******************************************
 * MetalType
 */
void PuckContext::MetalType::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[MetalType]->[TypeKnown]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) TypeKnown;
}
/*******************************************/

/*******************************************
 * TypeKnown
 */
void PuckContext::TypeKnown::switchOpen() {
	LOG_SCOPE;
	LOG_DEBUG << "[TypeKnown]->[SwitchArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//startTimers();
	new (this) SwitchArea;
}

void PuckContext::TypeKnown::slideIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[TypeKnown]->[SlideArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//startTimers();
	new (this) SlideArea;
}
/*******************************************/

/*******************************************
 * SlideArea
 */
void PuckContext::SlideArea::slideOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[SlideArea]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}

void PuckContext::SlideArea::lateTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[SlideArea]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::SLIDE_FULL;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
/*******************************************/

/*******************************************
 * SwitchArea
 */
void PuckContext::SwitchArea::outletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[SwitchArea]->[SwitchArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::SwitchArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[SwitchArea]->[SwitchTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) SwitchTimer;
}
/*******************************************/

/*******************************************
 * SwitchTimer
 */
void PuckContext::SwitchTimer::outletIn() {
	LOG_SCOPE;
#if !machine
	LOG_DEBUG << "[SwitchTimer]->[OutletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::SEND;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) OutletArea;
#else
	LOG_DEBUG << "[SwitchTimer]->[OutletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) OutletArea;
#endif
}
/*******************************************/

/*******************************************
 * OutletArea
 */
#if !machine
void PuckContext::OutletArea::serialAccept() {
	LOG_SCOPE;
	LOG_DEBUG << "[OutletArea]->[InTransfer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) InTransfer;
}
#else
void PuckContext::OutletArea::outletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[OutletArea]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
#endif
/*******************************************/

#if !machine
/*******************************************
 * InTransfer
 */
void PuckContext::InTransfer::serialStop() {
	LOG_SCOPE;
	LOG_DEBUG << "[InTransfer]->[TransferStopped]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) TransferStopped;
}

void PuckContext::InTransfer::outletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[InTransfer]->[Transferred]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) Transferred;
}
/*******************************************/

/*******************************************
 * TransferStopped
 */
void PuckContext::TransferStopped::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[TransferStopped]->[InTransfer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) InTransfer;
}
/*******************************************/

/*******************************************
 * Transferred
 */
void PuckContext::Transferred::serialReceived() {
	LOG_SCOPE;
	LOG_DEBUG << "[Transferred]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
/*******************************************/
#endif
