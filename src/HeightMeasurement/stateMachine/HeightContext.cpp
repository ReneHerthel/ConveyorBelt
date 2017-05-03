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

#define HEIGHT_SEND_PRIO    (0)
#define HEIGHT_PULSE_CODE   (141)

HeightContext::HeightContext(int send_chid)
    :    statePtr(&state)
    ,    send_chid(send_chid)
{
	statePtr->entry();
	state.chid = send_chid;
}

void HeightContext::process(Signal signal) {
    // Switch between defined signals and invoke the function of the statePtr.
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
            return; // Skip entry action.

        case RESUME:
            statePtr->resume();
            return;	// Skip entry action.

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
            std::cout<<"[HeightContext.cpp] Undefined signal."<<std::endl;
            return; // Do not do anything more.

    } /* switch (signal) */

    // Invoke the entry function of every new state.
    statePtr->entry();
}

void HeightContext::send(int chid, signal_t signal) {
    int err = MsgSendPulse_r(chid, sched_get_priority_min(HEIGHT_SEND_PRIO), HEIGHT_SEND_PRIO, signal.value);

    if (err < 0) {
        // TODO Error handling.
        std::cout<<"[measuringTask] Error on sending pulse message."<<std::endl;
    }
}

///
/// STATE
///
void HeightContext::State::entry() {
    new (this) Idle;
    std::cout<<"STATE - entry"<<std::endl;
}

void HeightContext::State::invalid() {
    std::cout<<"STATE - invalid"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::INVALID;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::timeout() {
    std::cout<<"STATE - timeout"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::TIMEOUT;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::start() {
    std::cout<<"STATE - start - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::wait() {
    // TODO stoptimer()
    std::cout<<"STATE - wait"<<std::endl;
}

void HeightContext::State::resume() {
    // TODO resumeTimer()
    std::cout<<"STATE - resume"<<std::endl;
}

void HeightContext::State::holeHeight() {
    std::cout<<"STATE - holeHeight - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::surfaceHeight() {
    std::cout<<"STATE - surfaceHeight - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::refHeight() {
    std::cout<<"STATE - refHeight - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::patternRead() {
    std::cout<<"STATE - patternRead - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::lowHeight() {
    std::cout<<"STATE - lowHeight - unexpected"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::UNEXPECTED;
    signal.pattern = 0;

    send(chid, signal);

    new (this) State;
}

void HeightContext::State::highHeight() {
    std::cout<<"STATE - highHeight - unexpected"<<std::endl;

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
    // TODO stopMeasuring()
    // TODO stopTimer()
    std::cout<<"IDLE - entry"<<std::endl;
}

void HeightContext::Idle::start() {
    std::cout<<"IDLE - start"<<std::endl;
    new (this) Measuring;
}

///
/// MEASURING : STATE
///
void HeightContext::Measuring::entry() {
    // TODO startMeasuring()
    // TODO startTimer()
    std::cout<<"MEASURING - entry"<<std::endl;
}

void HeightContext::Measuring::holeHeight() {
    std::cout<<"MEASURING - holeHeight"<<std::endl;
    new (this) Normal;
}

///
/// NORMAL : STATE
///
void HeightContext::Normal::entry() {
    std::cout<<"NORMAL - entry"<<std::endl;
}

void HeightContext::Normal::surfaceHeight() {
    std::cout<<"NORMAL - surfaceHeight"<<std::endl;
    new (this) Surface;
}

///
/// SURFACE : STATE
///
void HeightContext::Surface::entry() {
    std::cout<<"SURFACE - entry"<<std::endl;
}

void HeightContext::Surface::refHeight() {
    std::cout<<"SURFACE - refHeight"<<std::endl;

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
    std::cout<<"BITORFLIPPED - entry"<<std::endl;
    index = 0;
    //pattern = {0, 0, 0};
    new (this) Top;
}

void HeightContext::BitOrFlipped::patternRead() {
    std::cout<<"BITORFLIPPED - patternRead"<<std::endl;
    new (this) Idle;
}

///
/// TOP : BIT OR FLIPPED
///
void HeightContext::Top::entry() {
    std::cout<<"TOP - entry"<<std::endl;

    // Check if the index is in the range of the min/max bit size.
    if (index > MAX_BIT_SIZE || index < MIN_BIT_SIZE) {
        invalid();
    }
}

void HeightContext::Top::refHeight() {
    std::cout<<"TOP - refHeight"<<std::endl;

    // Check the value of the index to make sure the next transition is correct.
    if (index == 0) {
        new (this) Flipped;
    }
    else {
        new (this) BitCoded;
    }
}

void HeightContext::Top::lowHeight() {
    std::cout<<"TOP - lowHeight"<<std::endl;
    new (this) Low;
}

void HeightContext::Top::highHeight() {
    std::cout<<"TOP - highHeight"<<std::endl;
    new (this) High;
}

///
/// HIGH : BIT OR FLIPPED
///
void HeightContext::High::entry () {
    std::cout<<"HIGH - entry"<<std::endl;
    pattern[index] = 1;
    index++;
}

void HeightContext::High::surfaceHeight() {
    std::cout<<"HIGH - surfaceHeight"<<std::endl;
    new (this) Top;
}

///
/// LOW : BIT OR FLIPPED
///
void HeightContext::Low::entry() {
    std::cout<<"LOW - entry"<<std::endl;
    pattern[index] = 0;
    index++;
}

void HeightContext::Low::surfaceHeight() {
    std::cout<<"LOW - surfaceHeight"<<std::endl;
    new (this) Top;
}

///
/// FLIPPED : BIT OR FLIPPED
///
void HeightContext::Flipped::entry() {
    std::cout<<"FLIPPED - entry"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::FLIPPED;
    signal.pattern = 0;

    send(chid, signal);

    patternRead();
}

///
/// BITCODED : BIT OR FLIPPED
///
void HeightContext::BitCoded::entry() {
    std::cout<<"BITCODED - entry"<<std::endl;

    signal_t signal;
    signal.ID = SignalID::PATTERN;
    signal.BIT0 = pattern[0];
    signal.BIT1 = pattern[1];
    signal.BIT2 = pattern[2];

    send(chid, signal);

    patternRead();
}

/** @} */
