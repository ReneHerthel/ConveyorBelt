/*
 * PuckContext.cpp
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#include "PuckContext.h"

PuckContext::PuckContext() {

}

PuckReturn PuckContext::process() {

}

PuckReturn PuckContext::setType(signal_t type) {

}

void PuckContext::startTimers() {

}

/*******************************************
 * SuperState
 */
void PuckContext::PuckState::inletIn() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::inletOut() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::heightmeasurmentIn() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::heightmeasurmentOut() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::switchIn() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::switchOut() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::switchOpen() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::slideIn() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::slideOut() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::outletIn() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::outletOut() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::metalDetect() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::serialReceived() {
	returnVal = PuckContext::DENY;
}


void PuckContext::PuckState::earlyTimer() {
	returnVal = PuckContext::DENY;
}

void PuckContext::PuckState::lateTimer() {
	returnVal = PuckContext::ERROR;
}


PuckReturn entry() {
	return returnVal;
}
/*******************************************/

/*******************************************
 * TransferArea
 */
void PuckContext::TransferArea::inletIn() {
	returnVal = PuckContext::WARNING;
	new (this) TransferWarning;
}

void PuckContext::TransferArea::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) TransferTimer;
}

PuckReturn PuckContext::TransferArea::entry() {
	startTimers();
	return returnVal;
}
/*******************************************/

/*******************************************
 * TransferWarning
 */
void PuckContext::TransferWarning::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) TransferTimer;
}
/*******************************************/

/*******************************************
 * TransferTimer
 */
void PuckContext::TransferTimer::inletIn() {
	returnVal = PuckContext::ACCEPT;
	new (this) Inlet;
}
/*******************************************/

/*******************************************
 * Inlet
 */
void PuckContext::Inlet::inletOut() {
	returnVal = PuckContext::ACCEPT;
	new (this) InletArea;
}
/*******************************************/

/*******************************************
 * InletArea
 */
void PuckContext::InletArea::heightmeasurementIn() {
	returnVal = PuckContext::WARNING;
	new (this) WarningInlet;
}

void PuckContext::InletArea::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) InletTimer;
}
PuckReturn PuckContext::InletArea::entry() {
	startTimers();
	return returnVal;
}
/*******************************************/

/*******************************************
 * InletWarning
 */
void PuckContext::InletWarning::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) InletTimer;
}
/*******************************************/

/*******************************************
 * InletTimer
 */
void PuckContext::InletTimer::heightmeasurementIn() {
	returnVal = PuckContext::ACCEPT;
	new (this) Heightmeasurement;
}
/*******************************************/

/*******************************************
 * Heightmeasurement
 */
void PuckContext::Heightmeasurement::heightmeasurementOut() {
	returnVal = PuckContext::ACCEPT;
	new (this) MeasurementArea;
}
/*******************************************/

/*******************************************
 * MeasurementArea
 */
void PuckContext::MeasurementArea::switchIn() {
	returnVal = PuckContext::WARNING;
	new (this) MeasurementWarning;
}

void PuckContext::MeasurementArea::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) InletTimer;
}
PuckReturn PuckContext::MeasurementArea::entry() {
	startTimers();
	return returnVal;
}
/*******************************************/

/*******************************************
 * MeasurementWarning
 */
void PuckContext::MeasurementWarning::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) MeasurementTimer;
}
/*******************************************/

/*******************************************
 * MeasurementTimer
 */
void PuckContext::MeasurementTimer::switchIn() {
	returnVal = PuckContext::EVALUATE;
	new (this) TypeKnown;
}
void PuckContext::MeasurementTimer::MetalDetect(){
	returnVal = PuckContext::ACCEPT;
	context->metal = true;
	new (this) MetalType;
}
/*******************************************/

/*******************************************
 * MetalType
 */
void PuckContext::MetalType::switchIn() {
	returnVal = PuckContext::EVALUATE;
	new (this) TypeKnown;
}
/*******************************************/

/*******************************************
 * TypeKnown
 */
void PuckContext::TypeKnown::switchOpen() {
	returnVal = PuckContext::ACCEPT;
	new (this) SwitchArea;
}
void PuckContext::TypeKnown::slideIn(){
	returnVal = PuckContext::ACCEPT;
	new (this) SlideArea;
}
PuckReturn PuckContext::TypeKnown::entry() {
	startTimers();
	return returnVal;
}
/*******************************************/

/*******************************************
 * SlideArea
 */
void PuckContext::SlideArea::slideOut() {
	returnVal = PuckContext::DELETE;
	new (this) InSlide;
}
void PuckContext::SlideArea::LateTimer(){
	returnVal = PuckContext::SLIDE_FULL;
}

/*******************************************/

/*******************************************
 * SwitchArea
 */
void PuckContext::SwitchArea::switchIn() {
	returnVal = PuckContext::WARNING;
	new (this) SwitchWarning;
}

void PuckContext::SwitchArea::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) SwitchTimer;
}
PuckReturn PuckContext::SwitchArea::entry() {
	startTimers();
	return returnVal;
}
/*******************************************/

/*******************************************
 * SwitchWarning
 */
void PuckContext::SwitchWarning::earlyTimer() {
	returnVal = PuckContext::ACCEPT;
	new (this) MeasurementTimer;
}
/*******************************************/

/*******************************************
 * SwitchTimer
 */
void PuckContext::SwitchTimer::switchIn() {
	returnVal = PuckContext::ACCEPT;
	new (this) OutletArea;
}
/*******************************************/

/*******************************************
 * InTransfer
 */
void PuckContext::InTransfer::serialReceived() {
	returnVal = PuckContext::DELETE;
	new (this) Transferred;
}
/*******************************************/

