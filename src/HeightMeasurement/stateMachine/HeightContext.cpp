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

/*
 * @brief Macros for the sending method.
 * @{
 */
#define HEIGHT_SEND_PRIO    (0)
#define HEIGHT_PULSE_CODE   (141)
/** @} */

HeightContext::HeightContext(int send_chid, HeightMeasurementService *service)
    :    statePtr(&state)
    ,    service(service)
    ,    send_chid(send_chid)
{
    statePtr->entry();
    // The statemachine needs to know, where to send the signals.
    state.chid = send_chid;
    // All states needs to know the service class.
    state.service = service;
}

void HeightContext::process(Signal signal) {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG)

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

void HeightContext::send(int chid, signal_t signal) { // Static method.
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] send() chid: " << chid << " signal-ID: " << (int)signal.ID << "\n";

    int err = MsgSendPulse_r(chid, sched_get_priority_min(HEIGHT_SEND_PRIO), HEIGHT_SEND_PRIO, signal.value);

    if (err < 0) {
        // TODO Error handling.
        LOG_DEBUG << "[HeightContext] send() MsgSendPulse_r failed with: " << err << "\n";
    }
}

///
/// STATE
///
void HeightContext::State::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State entry()\n";
    new (this) Idle;
}

void HeightContext::State::invalid() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State invalid()\n";

    signal_t signal;
    signal.ID = SignalID::INVALID;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::timeout() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State timeout()\n";

    signal_t signal;
    signal.ID = SignalID::TIMEOUT;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::start() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State start()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::wait() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State wait()\n";
    // TODO stoptimer()
}

void HeightContext::State::resume() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State resume()\n";
    // TODO resumeTimer()
}

void HeightContext::State::holeHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State holeHeight()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::surfaceHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State surfaceHeight()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::refHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State refHeight()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::patternRead() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State patternRead()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::lowHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State lowHeight()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::highHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] State highHeight()\n";

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

///
/// IDLE : STATE
///
void HeightContext::Idle::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Idle entry()\n";

    service->stopMeasuring();
    // TODO stopTimer()
}

void HeightContext::Idle::start() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Idle startt()\n";
    new (this) Measuring;
}

///
/// MEASURING : STATE
///
void HeightContext::Measuring::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring entry()\n";

    service->startMeasuring();
    // TODO startTimer()
}

void HeightContext::Measuring::holeHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Measuring holeHeight()\n";
    new (this) Normal;
}

///
/// NORMAL : STATE
///
void HeightContext::Normal::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Normal entry()\n";
}

void HeightContext::Normal::surfaceHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Normal surfaceHeight()\n";
    new (this) Surface;
}

///
/// SURFACE : STATE
///
void HeightContext::Surface::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Surface entry()\n";
}

void HeightContext::Surface::refHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Surface refHeight()\n";

    signal_t signal;
    signal.ID = SignalID::NORMAL;
    signal.pattern = 0;

    send(chid, signal);

    new (this) Idle;
}

///
/// BIT OR FLIPPED : STATE
///
void HeightContext::BitOrFlipped::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitOrFlipped entry()\n";

    index = 0;
    //pattern = {0, 0, 0};
    new (this) Top;
}

void HeightContext::BitOrFlipped::patternRead() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitOrFlipped patternRead()\n";

    new (this) Idle;
}

///
/// TOP : BIT OR FLIPPED
///
void HeightContext::Top::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top entry()\n";

    // Check if the index is in the range of the min/max bit size.
    if (index > MAX_BIT_SIZE || index < MIN_BIT_SIZE) {
        invalid();
    }
}

void HeightContext::Top::refHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top refHeight()\n";

    // Check the value of the index to make sure the next transition is correct.
    if (index == 0) {
        new (this) Flipped;
    }
    else {
        new (this) BitCoded;
    }
}

void HeightContext::Top::lowHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top lowHeight()\n";

    new (this) Low;
}

void HeightContext::Top::highHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Top highHeight()\n";

    new (this) High;
}

///
/// HIGH : BIT OR FLIPPED
///
void HeightContext::High::entry () {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Hight entry()\n";

    pattern[index] = 1;
    index++;
}

void HeightContext::High::surfaceHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] High surfaceHeight()\n";

    new (this) Top;
}

///
/// LOW : BIT OR FLIPPED
///
void HeightContext::Low::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Low entry()\n";

    pattern[index] = 0;
    index++;
}

void HeightContext::Low::surfaceHeight() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Low surfaceHeight()\n";

    new (this) Top;
}

///
/// FLIPPED : BIT OR FLIPPED
///
void HeightContext::Flipped::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] Flipped entry()\n";

    signal_t signal;
    signal.ID = SignalID::FLIPPED;
    signal.pattern = 0;

    send(chid, signal);

    // Calls the super-method.
    patternRead();
}

///
/// BITCODED : BIT OR FLIPPED
///
void HeightContext::BitCoded::entry() {
    //LOG_SCOPE;
    LOG_SET_LEVEL(DEBUG);
    LOG_DEBUG << "[HeightContext] BitCoded entry()\n";

    signal_t signal;
    signal.ID = SignalID::PATTERN;
    signal.BIT0 = pattern[0];
    signal.BIT1 = pattern[1];
    signal.BIT2 = pattern[2];

    send(chid, signal);

    // Calls the super-method.
    patternRead();
}

/** @} */
