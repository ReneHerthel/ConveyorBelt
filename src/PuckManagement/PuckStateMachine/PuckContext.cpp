/*
 * PuckContext.cpp
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#include "PuckContext.h"

#include "Signals.h"

#include <new>

PuckContext::PuckContext(uint32_t puckID) {
#if !machine
	statePtr = &inletState;
#else
	statePtr = &transferState;
	startTimers();
#endif
	statePtr->puckID = puckID;
}

PuckSignal::Return PuckContext::process(PuckSignal::Signal signal) {
	switch(signal.signalType) {
		case PuckSignal::SignalType::HEIGHT_SIGNAL:
			statePtr->type();
			if(statePtr->returnValue.puckReturn == PuckSignal::PuckReturn::ACCEPT) {
				statePtr->puckType.heightType = signal.heightSignal;
			}
			break;

		case PuckSignal::SignalType::TIMER_SIGNAL:
			switch(signal.timerSignal.type) {
				case PuckSignal::TimerType::EARLY_TIMER:
					statePtr->earlyTimer();
					break;
				case PuckSignal::TimerType::LATE_TIMER:
					statePtr->lateTimer();
					break;
				default:
					;
					// todo: error handling
			}
			break;

		case PuckSignal::SignalType::INTERRUPT_SIGNAL:
			switch(signal.interruptSignal) {
				case INLET_IN:
					statePtr->inletIn();
					break;
				case INLET_OUT:
					statePtr->inletOut();
					break;
				case HEIGHTMEASUREMENT_IN:
					statePtr->heightmeasurmentIn();
					break;
				case HEIGHTMEASUREMENT_OUT:
					statePtr->heightmeasurmentOut();
					break;
				case interrupts::interruptSignals::METAL_DETECT:
					statePtr->puckType.metal = 1;
					statePtr->metalDetect();
					break;
				case SWITCH_IN:
					statePtr->switchIn();
					break;
				case SWITCH_OPEN:
					statePtr->switchOpen();
					break;
				case SLIDE_IN:
					statePtr->slideIn();
					break;
				case SLIDE_OUT:
					statePtr->slideOut();
					break;
				case OUTLET_IN:
					statePtr->outletIn();
					break;
				case OUTLET_OUT:
					statePtr->outletOut();
					break;
				default:
					// todo: error handling
					;
			}
			break;

		case PuckSignal::SignalType::SERIAL_SIGNAL:
			switch(signal.serialSignal) {
				case msg::ACCEPT:
					statePtr->serialAccept();
					break;
				case msg::STOP:
					statePtr->serialStop();
					break;
				case msg::RESUME:
					statePtr->serialResume();
					break;
				case msg::RECEIVED:
					statePtr->serialReceived();
					break;
				default:
					// todo: error handling
					;
			}
			break;
	}

	return statePtr->returnValue;
}

/*******************************************
 * SuperState
 */
void PuckContext::PuckState::inletIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::inletOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::heightmeasurmentIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::heightmeasurmentOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::switchIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::switchOpen() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::slideIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::slideOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::outletIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::outletOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::metalDetect() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::serialReceived() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}


void PuckContext::PuckState::earlyTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::PuckState::lateTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ERROR;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
}
/*******************************************/

#if machine
/*******************************************
 * TransferArea
 */
void PuckContext::TransferArea::inletIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
}

void PuckContext::TransferArea::earlyTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) TransferTimer;
}
/*******************************************/

/*******************************************
 * TransferTimer
 */
void PuckContext::TransferTimer::inletIn() {
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
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers();
	new (this) InletArea;
}
/*******************************************/

/*******************************************
 * InletArea
 */
void PuckContext::InletArea::heightmeasurementIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::InletArea::earlyTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) InletTimer;
}
/*******************************************/

/*******************************************
 * InletTimer
 */
void PuckContext::InletTimer::heightmeasurementIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::HEIGHT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) Heightmeasurement;
}
/*******************************************/

/*******************************************
 * Heightmeasurement
 */
void PuckContext::Heightmeasurement::heightmeasurementOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers();
	new (this) MeasurementArea;
}
void PuckContext::Heightmeasurement::type() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// todo: setType
}
/*******************************************/

/*******************************************
 * MeasurementArea
 */
void PuckContext::MeasurementArea::switchIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::MeasurementArea::earlyTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) MeasurementTimer;
}

void PuckContext::MeasurementArea::type() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// todo: setType
}
/*******************************************/

/*******************************************
 * MeasurementTimer
 */
void PuckContext::MeasurementTimer::switchIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) TypeKnown;
}

void PuckContext::MeasurementTimer::metalDetect() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// todo: setType
	new (this) MetalType;
}
/*******************************************/

/*******************************************
 * MetalType
 */
void PuckContext::MetalType::switchIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) TypeKnown;
}
/*******************************************/

/*******************************************
 * TypeKnown
 */
void PuckContext::TypeKnown::switchOpen() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers();
	new (this) SwitchArea;
}

void PuckContext::TypeKnown::slideIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers();
	new (this) SlideArea;
}
/*******************************************/

/*******************************************
 * SlideArea
 */
void PuckContext::SlideArea::slideOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}

void PuckContext::SlideArea::lateTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::SLIDE_FULL;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
/*******************************************/

/*******************************************
 * SwitchArea
 */
void PuckContext::SwitchArea::outletIn() {
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::SwitchArea::earlyTimer() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) SwitchTimer;
}
/*******************************************/

/*******************************************
 * SwitchTimer
 */
void PuckContext::SwitchTimer::outletIn() {
#if !machine
	returnValue.puckReturn = PuckSignal::PuckReturn::SEND;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) OutletArea;
#else
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
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) InTransfer;
}
#else
void PuckContext::OutletArea::outletOut() {
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
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) TransferStopped;
}

void PuckContext::InTransfer::outletOut() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) Transferred;
}
/*******************************************/

/*******************************************
 * TransferStopped
 */
void PuckContext::TransferStopped::serialResume() {
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) InTransfer;
}
/*******************************************/

/*******************************************
 * Transferred
 */
void PuckContext::Transferred::serialReceived() {
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
/*******************************************/
#endif
