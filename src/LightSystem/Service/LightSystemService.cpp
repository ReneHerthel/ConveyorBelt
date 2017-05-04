// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

LightSystemService::LightSystemService(int chid):
    chid(chid)
{};

void LightSystemService::setWarningLevel(Level warningLevel) {
	LOG_SCOPE;
    /* FIXME: Discuss Priorities */
    /* TODO: Merge messages */
    /* 80 is ID for lightSystem */
    LOG_DEBUG << "Send message | Channel " << chid << " | ID " << LIGHT_SYSTEM << " | Warning Level " << warningLevel << endl;
    int err = MsgSendPulse_r(chid, sched_get_priority_min(0), LIGHT_SYSTEM, warningLevel);
    if(err) {
        LOG_ERROR << "Sending message failed" << endl;
    }
}
