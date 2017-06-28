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
#include <iostream>
#include <sstream>
#include <new>

PuckContext::PuckContext(int chid, PuckSignal::PuckType puckType, uint16_t puckId) : shortDistance(chid, TIMERCODE), wideDistance(chid, TIMERCODE) {
	LOG_SCOPE;

#if !machine
	LOG_DEBUG << "Using machine0\n";
	statePtr = &inletState;
	setPuckID(puckId);
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	statePtr->shortDistance = &shortDistance;
	statePtr->wideDistance = &wideDistance;

#else
	LOG_DEBUG << "Using machine1" << endl;
	statePtr = &transferState;
	setPuckID(puckId);
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	statePtr->shortDistance = &shortDistance;
	statePtr->wideDistance = &wideDistance;

	statePtr->startTimersWithDelta(DistanceSpeed::lb_distance::OUT_TO_IN, QUICK_SHORT_DELTA, VERY_WIDE_DELTA); //we want a quick earlytimer but a very late Latetimer
#endif

	// set invalid value for height signal - in case heightmeasurement gets stuck
	statePtr->puckType = puckType;
}

PuckContext::PuckContext(int chid) : shortDistance(chid, TIMERCODE), wideDistance(chid, TIMERCODE) {
	LOG_SCOPE;

#if !machine
	LOG_DEBUG << "Using machine0\n";
	statePtr = &inletState;
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	statePtr->shortDistance = &shortDistance;
	statePtr->wideDistance = &wideDistance;

#else
	LOG_DEBUG << "Using machine1\n";
	statePtr = &transferState;
	statePtr->returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	statePtr->shortDistance = &shortDistance;
	statePtr->wideDistance = &wideDistance;

	statePtr->startTimersWithDelta(DistanceSpeed::lb_distance::OUT_TO_IN, QUICK_SHORT_DELTA, VERY_WIDE_DELTA); //we want a quick earlytimer but a very late Latetimer
#endif

	// set invalid value for height signal - in case heightmeasurement gets stuck
	statePtr->puckType.data.heightType.value = 0;
	statePtr->puckType.data.height1 = 0;
	statePtr->puckType.data.height2 = 0;
	statePtr->puckType.data.metal = false;
}

PuckSignal::Return PuckContext::process(PuckSignal::Signal signal) {
	LOG_SCOPE;
	switch(signal.signalType) {
		case PuckSignal::SignalType::HEIGHT_SIGNAL:
			LOG_DEBUG << "Signal is a height signal\n";
			statePtr->type();
			if(statePtr->returnValue.puckReturn == PuckSignal::PuckReturn::ACCEPT) {
				statePtr->puckType.data.heightType = signal.heightSignal;
#if !machine
				statePtr->puckType.data.height1 = signal.heightSignal.highestHeight;
#else
				statePtr->puckType.data.height2 = signal.heightSignal.highestHeight;
#endif
			}
			break;

		case PuckSignal::SignalType::TIMER_SIGNAL:
			LOG_DEBUG << "Signal is a timer signal\n";
			switch(signal.timerSignal.TimerInfo.type) {
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
					statePtr->returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
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
				case interrupts::interruptSignals::SWITCH_OUT:
					LOG_DEBUG << "Signal is switch_out\n";
					statePtr->switchOut();
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
					statePtr->returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
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
					statePtr->returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
			}
			break;

		default:
			LOG_DEBUG << "Unknown signal\n";
			statePtr->returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
	}

	return statePtr->returnValue;
}

/*************************************************************************************************
 * TIMERMETHODS
 */

void PuckContext::PuckState::startTimers(DistanceSpeed::lb_distance distance) {
	LOG_SCOPE;
	LOG_DEBUG <<"[Puck" + std::to_string(puckID) + "] Started Timers" << endl;
	PuckSignal::TimerSignal ts;
	ts.TimerInfo.puckID = puckID;
	ts.TimerInfo.type = PuckSignal::TimerType::EARLY_TIMER;
	shortDistance->startAlarm(ts.value,distance,SHORT_DELTA);
	ts.TimerInfo.type = PuckSignal::TimerType::LATE_TIMER;
	wideDistance->startAlarm(ts.value,distance,WIDE_DELTA);

}

void PuckContext::PuckState::startTimersWithDelta(DistanceSpeed::lb_distance distance,double earlyDelta,double lateDelta) {
	LOG_SCOPE;
	LOG_DEBUG <<"[Puck" + std::to_string(puckID) + "] Started Timers with Delta" << endl;
	PuckSignal::TimerSignal ts;
	ts.TimerInfo.puckID = puckID;
	ts.TimerInfo.type = PuckSignal::TimerType::EARLY_TIMER;
	shortDistance->startAlarm(ts.value,distance,earlyDelta);
	ts.TimerInfo.type = PuckSignal::TimerType::LATE_TIMER;
	wideDistance->startAlarm(ts.value,distance,lateDelta);

}
void PuckContext::PuckState::stopTimer(){
	LOG_SCOPE;
	LOG_DEBUG <<"[Puck" + std::to_string(puckID) + "] Stopped Timer" << endl;
	wideDistance->stopAlarm();
}
/*************************************************************************************************
 * TOSTRING
 */

std::string PuckContext::PuckState::toString(){

	std:stringstream outString;

	outString << "[ACCEPTED PUCK] \n PuckID: " << std::to_string(puckID) << "\n";
	switch(puckType.data.heightType.ID){
		case HeightMeasurement::INVALID_ID :
			outString <<"PuckType: INVALID \n";
			break;
		case HeightMeasurement::NORMAL_ID :
			if(puckType.data.metal) {
				outString << "PuckType: METAL  \n";
			} else {
				outString << "PuckType: NORMAL  \n";
			}
			break;
		case HeightMeasurement::FLIPPED_ID :
			outString << "PuckType: FLIPPED  \n";
			break;
		case HeightMeasurement::PATTERN_ID :
			outString << "PuckType: BITPATTERN: " << std::to_string(puckType.data.heightType.BIT0)
							<< puckType.data.heightType.BIT1
							<< puckType.data.heightType.BIT2 << "\n";
			break;
		case HeightMeasurement::UNEXPECTED_ID :
			outString << "PuckType: UNEXPECTED  \n";
			break;
		default :
			LOG_DEBUG <<"[PUCK toString()] unexpected Signal" <<endl;
	}
	outString << "Height1: " << std::to_string(puckType.data.height1) <<
			"\nHeight2: " << std::to_string(puckType.data.height1) << "\n";
	return outString.str();
}


/*******************************************
 * SuperState
 */
void PuckContext::PuckState::inletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::inletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::heightmeasurementIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::heightmeasurementOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::switchOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::slideIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::slideOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::outletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::outletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::metalDetect() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::serialAccept() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialReceived() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialStop() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}


void PuckContext::PuckState::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DENY;
}

void PuckContext::PuckState::lateTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [PuckState]->[PuckState]\n";
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
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferArea]->[TransferArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
}

void PuckContext::TransferArea::serialStop() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferArea]->[TransferArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) TransferStoppedInlet;
}

void PuckContext::TransferArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferArea]->[TransferTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) TransferTimer;
}
/*******************************************/

/*******************************************
 * TransferStoppedInlet
 */
void PuckContext::TransferStoppedInlet::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferStoppedInlet]->[TransferArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) TransferArea;
}

/*******************************************/

/*******************************************
 * TransferTimer
 */
void PuckContext::TransferTimer::inletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferTimer]->[Inlet]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::RECEIVED;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	stopTimer();
	new (this) Inlet;
}

void PuckContext::TransferTimer::serialStop() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferTimer]->[TransferStoppedInletTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) TransferStoppedInletTimer;
}
/*******************************************/


/*******************************************
 * TransferStoppedInlet
 */
void PuckContext::TransferStoppedInletTimer::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferStoppedInletTimer]->[TransferTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) TransferTimer;
}

/*******************************************/
#endif

/*******************************************
 * Inlet
 */
void PuckContext::Inlet::inletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [Inlet]->[InletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers(DistanceSpeed::lb_distance::INLET_TO_HEIGHT);
	new (this) InletArea;
}
/*******************************************/

/*******************************************
 * InletArea
 */
void PuckContext::InletArea::heightmeasurementIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InletArea]->[InletArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::InletArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InletArea]->[InletTimer]\n";
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
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InletTimer]->[Heightmeasurement]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::START_HEIGHT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	stopTimer();
	new (this) Heightmeasurement;
}
/*******************************************/

/*******************************************
 * Heightmeasurement
 */
void PuckContext::Heightmeasurement::heightmeasurementOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [Heightmeasurement]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::STOP_HEIGHT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers(DistanceSpeed::lb_distance::HEIGHT_TO_SWITCH);
	new (this) MeasurementArea;
}
void PuckContext::Heightmeasurement::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [Heightmeasurement]->[Heightmeasurement]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}
/*******************************************/

/*******************************************
 * MeasurementArea
 */
void PuckContext::MeasurementArea::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MeasurementArea]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::MeasurementArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MeasurementArea]->[MeasurementTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) MeasurementTimer;
}

/* -- makes problems
void PuckContext::MeasurementArea::type() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MeasurementArea]->[MeasurementArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}
*/
/*******************************************/

/*******************************************
 * MeasurementTimer
 */
void PuckContext::MeasurementTimer::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MeasurementTimer]->[TypeKnown]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	stopTimer();
	new (this) TypeKnown;
}

void PuckContext::MeasurementTimer::metalDetect() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MeasurementTimer]->[MetalType]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	puckType.data.metal = 1;
	new (this) MetalType;
}
/*******************************************/

/*******************************************
 * MetalType
 */
void PuckContext::MetalType::switchIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [MetalType]->[TypeKnown]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::EVALUATE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	stopTimer();
	new (this) TypeKnown;
}
/*******************************************/

/*******************************************
 * TypeKnown
 */
void PuckContext::TypeKnown::switchOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TypeKnown]->[SwitchArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	startTimers(DistanceSpeed::lb_distance::SWITCH_TO_OUTLET);
	new (this) SwitchArea;
}


/*******************************************/

/*******************************************
 * SwitchArea
 */
void PuckContext::SwitchArea::outletIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchArea]->[SwitchArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::WARNING;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
}

void PuckContext::SwitchArea::earlyTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchArea]->[SwitchTimer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	new (this) SwitchTimer;
}

void PuckContext::SwitchArea::slideIn() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchArea]->[SlideArea]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	//clear timers from switch to out distance
	shortDistance->stopAlarm();
	wideDistance->stopAlarm();

	PuckSignal::TimerSignal ts;
	ts.TimerInfo.puckID = puckID;
	ts.TimerInfo.type = PuckSignal::TimerType::LATE_TIMER;
	wideDistance->startAlarm(ts.value,DistanceSpeed::lb_distance::SLIDE,WIDE_DELTA);   //is made here because only one Timer is needed

	new (this) SlideArea;
}
/*******************************************/

/*******************************************
 * SlideArea
 */
void PuckContext::SlideArea::slideOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SlideArea]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	stopTimer();
	// dies here
}

void PuckContext::SlideArea::lateTimer() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SlideArea]->[SlideFull]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::SLIDE_FULL;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLIDE_STOP;
	new (this) SlideFull;
}
/*******************************************/


/*******************************************
 * SlideFull
 */
void PuckContext::SlideFull::slideOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SlideFull]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::SLIDE_EMPTY;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLIDE_STOP;
	// dies here
}
/*******************************************/

/*******************************************
 * SwitchTimer
 */
void PuckContext::SwitchTimer::outletIn() {
	LOG_SCOPE;
#if ONE_MACHINE_TESTING
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchTimer]->[InTransfer] JUST FOR TESTING WITHOUT SERIAL\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	stopTimer();
	new (this) InTransfer;
#else

	#if !machine
		LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchTimer]->[OutletArea]\n";
		returnValue.puckReturn = PuckSignal::PuckReturn::SEND;
		returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
		stopTimer();
		new (this) OutletArea;
	#else
		LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [SwitchTimer]->[OutletArea]\n";
		returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
		returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
		stopTimer();
		new (this) OutletArea;
	#endif
#endif


}
/*******************************************/

/*******************************************
 * OutletArea
 */
#if !machine
void PuckContext::OutletArea::serialAccept() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [OutletArea]->[InTransfer]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) InTransfer;
}
#else
void PuckContext::OutletArea::outletOut() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [OutletArea]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLIDE_STOP;
	/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Printing puck infos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
	std::cout << toString() << "\n";
	std::cout.flush();

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
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InTransfer]->[TransferStopped]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::STOP;
	new (this) TransferStopped;
}

void PuckContext::InTransfer::outletOut() {
	LOG_SCOPE;
#if ONE_MACHINE_TESTING
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InTransfer]->[dead] JUST FOR TESTING WITHOUT SERIAL\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;

#else
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [InTransfer]->[Transferred]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::ACCEPT;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::SLOW;
	new (this) Transferred;
#endif
}
/*******************************************/

/*******************************************
 * TransferStopped
 */
void PuckContext::TransferStopped::serialResume() {
	LOG_SCOPE;
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [TransferStopped]->[InTransfer]\n";
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
	LOG_DEBUG << "[Puck" + std::to_string(puckID) + "] [Transferred]->[dead]\n";
	returnValue.puckReturn = PuckSignal::PuckReturn::DELETE;
	returnValue.puckSpeed = PuckSignal::PuckSpeed::FAST;
	// dies here
}
/*******************************************/
#endif
