// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

LightSystemService::LightSystemService(int coid):
    coid(coid)
{};

void LightSystemService::setWarningLevel(Level warningLevel) {
    /* FIXME: Discuss Priorities */
    /* TODO: Merge messages */
    /* 80 is ID for lightSystem */
    int err = MsgSendPulse_r(coid, sched_get_priority_min(0),LIGHT_SYSTEM,warningLevel);

    if(err) {
        // TODO: Dump to log
    }
}
