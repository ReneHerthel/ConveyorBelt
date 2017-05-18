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
#include "Logger.h"
#include "LogScope.h"

#include <sys/siginfo.h>
#include <sys/neutrino.h>

#include <iostream>

HeightContext::HeightContext(int send_chid, HeightMeasurementService *service)
    :    statePtr(&state)
    ,    service(service)
{

	LOG_SCOPE;
	//LOG_SET_LEVEL(DEBUG)
    // All states needs to know the service class.
    state.service = service;

    // Connect, so the state machine can send signals to the send_chid.
    coid = ConnectAttach_r(ND_LOCAL_NODE, 0, send_chid, 0, 0);

    // The statemachine needs to know, where to send the signals.
    state.coid = coid;

    LOG_DEBUG << "[HeightContext] HeightContext() send_chid: " << send_chid << " coid is: " << state.coid << "\n";

    if (coid < 0) {
        // TODO: Error handling.
        LOG_DEBUG << "[HeightContext] HeightContext() ConnectAttach_r failed\n";

    }

    statePtr->entry();
}

void HeightContext::process(Signal signal) {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG)

    // Switch between defined signals and invoke the function of the statePtr.
    switch(signal) {

        case INVALID:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: INVALID\n";
            statePtr->invalid();
            break;

        case TIMEOUT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: TIMEOUT\n";
            statePtr->timeout();
            break;

        case START:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: START\n";
            statePtr->start();
            break;

        case WAIT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: WAIT\n";
            statePtr->wait();
            return; // Skip entry action.

        case RESUME:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: RESUME\n";
            statePtr->resume();
            return;	// Skip entry action.

        case HOLE_HEIGHT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: HOLE_HEIGHT\n";
            statePtr->holeHeight();
            break;

        case SURFACE_HEIGHT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: SURFACE_HEIGHT\n";
            statePtr->surfaceHeight();
            break;

        case REF_HEIGHT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: REF_HEIGHT\n";
            statePtr->refHeight();
            break;

        case PATTERN_READ:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: PATTERN_READ\n";
            statePtr->patternRead();
            break;

        case LOW_HEIGHT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: LOW_HEIGHT\n";
            statePtr->lowHeight();
            break;

        case HIGH_HEIGHT:
            LOG_DEBUG << "[HeightContext] process() Incoming signal: HIGH_HEIGHT\n";
            statePtr->highHeight();
            break;

        default:
            LOG_DEBUG << "[HeightContext] process() Undefined signal\n";
            return; // Do not do anything more.

    } /* switch (signal) */

    // Invoke the entry function of every new state.
    statePtr->entry();
}

void HeightContext::send(int coid, signal_t signal) { // Static method.
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);

    int err = MsgSendPulse_r(coid, sched_get_priority_min(0), 0, (int)signal.value); // TODO: Fix the magic-numbers.

    LOG_DEBUG << "[HeightContext] send() coid: " << coid << " signal-ID: " << (int)signal.ID << " CODE: " << (int)signal.BIT0 << (int)signal.BIT1 << (int)signal.BIT2 << "\n";

    //std::cout << "HEX: " << std::hex << (int)signal.value << std::endl;
    LOG_DEBUG << "DUMMY MESSAGE\n";

    if (err < 0) {
        // TODO Error handling.
    	//LOG_SET_LEVEL(DEBUG);
        LOG_DEBUG << "[HeightContext] send() MsgSendPulse_r failed with: " << err << "\n";
    }
}

///
/// STATE
///
void HeightContext::State::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State entry()\n";
    new (this) Idle;
}

void HeightContext::State::invalid() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State invalid()\n";

    // do nothing
}

void HeightContext::State::timeout() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State timeout()\n";

    signal_t signal;
    signal.ID = SignalID::TIMEOUT_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

    send(coid, signal);

    new (this) Idle;
}

void HeightContext::State::start() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State start()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

    send(coid, signal);

    new (this) Idle;
}

void HeightContext::State::wait() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State wait()\n";
    // TODO stoptimer()
}

void HeightContext::State::resume() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State resume()\n";
    // TODO resumeTimer()
}

void HeightContext::State::holeHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State holeHeight()\n";

    // do nothing
}

void HeightContext::State::surfaceHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State surfaceHeight()\n";

    // do nothing
}

void HeightContext::State::refHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State refHeight()\n";

    // do nothing
}

void HeightContext::State::patternRead() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State patternRead()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

    send(coid, signal);

    new (this) Idle;
}

void HeightContext::State::lowHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State lowHeight()\n";

    // do nothing
}

void HeightContext::State::highHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State highHeight()\n";

    // do nothing
}

///
/// IDLE : STATE
///
HeightContext::Idle::Idle() {

	if (service != NULL) {
	    service->stopMeasuring();
	}

    index = 0;
}

void HeightContext::Idle::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Idle entry()\n";

    // TODO stopTimer()
}

void HeightContext::Idle::start() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Idle start()\n";
    new (this) Measuring;
}

///
/// MEASURING : STATE
///
void HeightContext::Measuring::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring entry()\n";

    if (service != NULL) {
        service->startMeasuring();
    }
    // TODO startTimer()
}

void HeightContext::Measuring::invalid() {
	//LOG_SCOPE;
	//LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG << "[HeightContext] Measuring invalid()\n";

	signal_t signal;
	signal.ID = SignalID::INVALID_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

	send(coid, signal);

	new (this) Idle;
}

void HeightContext::Measuring::surfaceHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring surfaceHeight()\n";
    new (this) BitOrFlipped;
}

void HeightContext::Measuring::highHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring highHeight()\n";
    new (this) High;
}

void HeightContext::Measuring::lowHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring lowHeight()\n";
    new (this) Low;
}

void HeightContext::Measuring::holeHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring holeHeight()\n";
    new (this) Normal;
}

///
/// NORMAL : STATE
///
void HeightContext::Normal::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Normal entry()\n";
}

void HeightContext::Normal::surfaceHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Normal surfaceHeight()\n";
    new (this) Surface;
}

///
/// SURFACE : STATE
///
void HeightContext::Surface::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Surface entry()\n";
}

void HeightContext::Surface::refHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Surface refHeight()\n";

    signal_t signal;
    signal.ID = SignalID::NORMAL_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

    send(coid, signal);

    new (this) Idle;
}

///
/// BIT OR FLIPPED : STATE
///
void HeightContext::BitOrFlipped::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitOrFlipped entry()\n";

    //pattern = {0, 0, 0};
    new (this) Top;
}

void HeightContext::BitOrFlipped::patternRead() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitOrFlipped patternRead()\n";

    new (this) Idle;
}

///
/// TOP : BIT OR FLIPPED
///
void HeightContext::Top::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top entry()\n";

    // Check if the index is in the range of the min/max bit size.
    if (index > MAX_BIT_SIZE) {
    	LOG_DEBUG << "[HeightContext] Top entry() index{" << index << "} > MAX_BIT_SIZE\n";

    	signal_t signal;
		signal.ID = SignalID::INVALID_ID;
	    signal.BIT0 = 0;
	    signal.BIT1 = 0;
	    signal.BIT2 = 0;

		send(coid, signal);

		new (this) Idle;
    }
}

void HeightContext::Top::refHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top refHeight()\n";

    // Check the value of the index to make sure the next transition is correct.
    if (index == 0) {
        new (this) Flipped;

    } else if (index < MIN_BIT_SIZE) {

    	LOG_DEBUG << "[HeightContext] Top refHeight() index{" << index << "} < MIN_BIT_SIZE\n";
    	signal_t signal;
    	signal.ID = SignalID::INVALID_ID;
        signal.BIT0 = 0;
        signal.BIT1 = 0;
        signal.BIT2 = 0;

   		send(coid, signal);

   		new (this) Idle;

    } else {
        new (this) BitCoded;
    }
}

void HeightContext::Top::lowHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] TOP ---> LOW\n";

    new (this) Low;
}

void HeightContext::Top::highHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] TOP ---> HIGH\n";

    new (this) High;
}

///
/// HIGH : BIT OR FLIPPED
///
HeightContext::High::High() {

    pattern[index] = 1;
    index++;

    LOG_DEBUG << "[HeightContext] High High() index{" << index << "}\n";
}

void HeightContext::High::entry() {
	// We need this function, so the super function will not be called.
}

void HeightContext::High::surfaceHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] HIGH ---> TOP\n";

    new (this) Top;
}

///
/// LOW : BIT OR FLIPPED
///
HeightContext::Low::Low() {
    pattern[index] = 0;
    index++;

    LOG_DEBUG << "[HeightContext] Low Low() index{" << index << "}\n";
}

void HeightContext::Low::entry() {
	// We need this function, so the super function will not be called.
}

void HeightContext::Low::surfaceHeight() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] LOW  ---> TOP\n";

    new (this) Top;
}

///
/// FLIPPED : BIT OR FLIPPED
///
void HeightContext::Flipped::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Flipped entry()\n";

    signal_t signal;
    signal.ID = SignalID::FLIPPED_ID;
    signal.BIT0 = 0;
    signal.BIT1 = 0;
    signal.BIT2 = 0;

    send(coid, signal);

    patternRead();  // Calls the super-method.
}

///
/// BITCODED : BIT OR FLIPPED
///
void HeightContext::BitCoded::entry() {
    //LOG_SCOPE;
    //LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitCoded entry()\n";

    signal_t signal;
    signal.ID = SignalID::PATTERN_ID;
    signal.BIT0 = pattern[0];
    signal.BIT1 = pattern[1];
    signal.BIT2 = pattern[2];

    send(coid, signal);

    patternRead();  // Calls the super-method.
}

/** @} */
