/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    height_context
  * @{
  *
  * @brief      Statemachine for the height measurement.
  *
  * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "HeightContext.h"
#include <iostream>
#include <sys/siginfo.h>
#include <sys/neutrino.h>

HeightContext::HeightContext(int send_chid)
: statePtr(&state)
, send_chid(send_chid)
{
	statePtr->entry();
}

void HeightContext::process(Signal signal) {
	switch(signal) {

		case INVALID:
			statePtr->invalid();
			break;

		case TIMEOUT:
			statePtr->timeout();
			break;

		case START:
			statePtr->start();
			break;

		case WAIT:
			statePtr->wait();
			break;

		case RESUME:
			statePtr->resume();
			break;

		case HOLE_HEIGHT:
			statePtr->holeHeight();
			break;

		case SURFACE_HEIGHT:
			statePtr->surfaceHeight();
			break;

		case REF_HEIGHT:
			statePtr->refHeight();
			break;

		case PATTERN_READ:
			statePtr->patternRead();
			break;

		case LOW_HEIGHT:
			statePtr->lowHeight();
			break;

		case HIGH_HEIGHT:
			statePtr->highHeight();
			break;

		default:
			std::cout<<"Process() - Undefined Signal"<<std::endl;
			break;
	}

	statePtr->entry();
}

///
/// STATE
///
void HeightContext::State::entry() {
	std::cout<<"STATE - ENTRY"<<std::endl;
	new (this) Idle;
}

void HeightContext::State::invalid() {
	// todo MsgSendPulse_r(invalid)
	std::cout<<"STATE - INVALID"<<std::endl;
	new (this) State;
}

void HeightContext::State::timeout() {
	// todo MsgSendPulse_r(timeout)
	std::cout<<"STATE - TIMEOUT"<<std::endl;
	new (this) State;
}

void HeightContext::State::start() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::wait() {
	// todo stoptimer()
	std::cout<<"STATE - stopTimer()"<<std::endl;
}

void HeightContext::State::resume() {
	// todo resumeTimer()
	std::cout<<"STATE - resumeTimer()"<<std::endl;
}

void HeightContext::State::holeHeight() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::surfaceHeight() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::refHeight() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::patternRead() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::lowHeight() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

void HeightContext::State::highHeight() {
	// todo MsgSendPulse_r(unexpected)
	std::cout<<"STATE - UNEXPECTED"<<std::endl;
	new (this) State;
}

///
/// IDLE
///
void HeightContext::Idle::entry() {
	// todo stopMeasuring()
	// todo stopTimer()
	std::cout<<"Idle"<<std::endl;
}

void HeightContext::Idle::start() {
	new (this) Measuring;
}

///
/// MEASURING
///
void HeightContext::Measuring::entry() {
	// todo startMeasuring()
	// todo startTimer()
	std::cout<<"Measuring"<<std::endl;
}

void HeightContext::Measuring::holeHeight() {
	new (this) Normal;
}

///
/// NORMAL
///
void HeightContext::Normal::entry() {
	std::cout<<"Normal"<<std::endl;
}

void HeightContext::Normal::surfaceHeight() {
	new (this) Surface;
}

///
/// SURFACE
///
void HeightContext::Surface::entry() {
	std::cout<<"Surface"<<std::endl;
}

void HeightContext::Surface::refHeight() {
	new (this) Idle;
}

///
/// BIT OR FLIPPED
///
void HeightContext::BitOrFlipped::entry() {
	std::cout<<"BitOrFlipped"<<std::endl;
	index = 0;
	//pattern = {0, 0, 0};
	new (this) Top;
}

void HeightContext::BitOrFlipped::patternRead() {
	new (this) Idle;
}

///
/// Top
///
void HeightContext::Top::entry() {
	std::cout<<"Top"<<std::endl;
	if (index > MAX_BIT_SIZE || index < MIN_BIT_SIZE) {
		invalid();
	}
}

void HeightContext::Top::refHeight() {
	if (index == 0) {
		new (this) Flipped;
	}
	else {
		new (this) BitCoded;
	}
}

void HeightContext::Top::lowHeight() {
	new (this) Low;
}

void HeightContext::Top::highHeight() {
	new (this) High;
}

///
/// HIGH
///
void HeightContext::High::entry () {
	std::cout<<"High"<<std::endl;
	pattern[index] = 1;
	index++;
}

void HeightContext::High::surfaceHeight() {
	new (this) Top;
}

///
/// LOW
///
void HeightContext::Low::entry() {
	std::cout<<"Low"<<std::endl;
	pattern[index] = 0;
	index++;
}

void HeightContext::Low::surfaceHeight() {
	new (this) Top;
}

///
/// FLIPPED
///
void HeightContext::Flipped::entry() {
	std::cout<<"Flipped"<<std::endl;
	//todo msgSend(flipped)
	std::cout<<"fLIPPED - msgSend(Flipped)"<<std::endl;
	patternRead();
}

///
/// BITCODED
///
void HeightContext::BitCoded::entry() {
	std::cout<<"BitCoded"<<std::endl;
	//todo msgSend(pattern)
	std::cout<<"BitCoded - msgSend(Pattern)"<<std::endl;
	patternRead();
}

/** @} */
