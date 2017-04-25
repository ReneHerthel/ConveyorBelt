// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

void LightSystemService(coid):
    coid(coid)
{};

void LightSystemService::setWarningLevel(Level warningLevel) {
    /* TODO: Make static and share among class instances */
    const LightMessage LightMessageMapping[] = {
            { GREEN, ALWAYS_ON }, // OPERATING
            { GREEN, ALWAYS_OFF }, // NOT_OPERATING
            { YELLOW, SLOW_BLINKING }, // WARNING
            { YELLOW, ALWAYS_OFF }, // CLEAR_WARNING 
            { RED, ALWAYS_OFF }, // CLEAR_ERROR
            { RED, FAST_BLINKING }, // ERROR_OCCURED
            { RED, ALWAYS_ON }, // ERROR_ACKNOWLEDGED
            { RED, SLOW_BLINKING }, // ERROR_GONE_UNACKNOWLEDGED
            { ALL, ALWAYS_OFF } // CLEAR_ALL
    }; 

    LightMessage value = LightMessageMapping[warningLevel];
    /* TODO: Send pulse message */
    //res = MsgSendPulse ( coid, priority, code, value ) ;
}
