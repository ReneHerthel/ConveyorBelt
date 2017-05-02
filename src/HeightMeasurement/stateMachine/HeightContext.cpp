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

HeightContext::HeightContext(int send_chid)
    :    statePtr(&state)
    ,    send_chid(send_chid)
{
    // Make sure the first state is calling the entry function.
    statePtr->entry();
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
            std::cout<<"[HeightContext.cpp] Undefined signal."<<std::endl;
            return; // Do not do anything more.

    } /* switch (signal) */

    // Invoke the entry function of every new state.
    statePtr->entry();
}

///
/// STATE
///
void HeightContext::State::entry() {
    std::cout<<"STATE - entry"<<std::endl;
    new (this) Idle;
}

void HeightContext::State::invalid() {
    // TODO MsgSendPulse_r(invalid)
    //int err = MsgSendPulse_r(send_chid, sched_get_priority_min(HEIGHT_SEND_PRIO), 0);
    std::cout<<"STATE - invalid"<<std::endl;
    new (this) State;
}

void HeightContext::State::timeout() {
    // TODO MsgSendPulse_r(timeout)
    std::cout<<"STATE - timeout"<<std::endl;
    new (this) State;
}

void HeightContext::State::start() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - start - unexpected"<<std::endl;
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
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - holeHeight - unexpected"<<std::endl;
    new (this) State;
}

void HeightContext::State::surfaceHeight() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - surfaceHeight - unexpected"<<std::endl;
    new (this) State;
}

void HeightContext::State::refHeight() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - refHeight - unexpected"<<std::endl;
    new (this) State;
}

void HeightContext::State::patternRead() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - patternRead - unexpected"<<std::endl;
    new (this) State;
}

void HeightContext::State::lowHeight() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - lowHeight - unexpected"<<std::endl;
    new (this) State;
}

void HeightContext::State::highHeight() {
    // TODO MsgSendPulse_r(unexpected)
    std::cout<<"STATE - highHeight - unexpected"<<std::endl;
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
    //TODO msgSend(flipped)
    patternRead();
}

///
/// BITCODED : BIT OR FLIPPED
///
void HeightContext::BitCoded::entry() {
    std::cout<<"BITCODED - entry"<<std::endl;
    //TODO msgSend(pattern)
    patternRead();
}

/** @} */
