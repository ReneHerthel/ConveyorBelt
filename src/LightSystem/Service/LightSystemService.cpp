/**
 *       @file  LightSystemService.cpp
 *      @brief  Implementation for service class
 *
 * Hides pulse messaging for communication with the controller.
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/06/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#include "LightSystemService.h"

LightSystemService::LightSystemService(int chid):
    chid(chid)
{};

void LightSystemService::setWarningLevel(Level warningLevel) {
//	LOG_SCOPE;
    /* FIXME: Discuss Priorities */
    /* 80 is ID for lightSystem */
	int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, chid, 0, 0);
	if(coid < 0) {
        /* FIXME: Discuss sane error handling for message infrastructure failure */
	//   	LOG_ERROR << "Channel Attach failed" << endl;
	}

    /* FIXME: Discuss log message format */
	//LOG_DEBUG << "Send message | Channel " << chid << " | ID " << LIGHT_SYSTEM << " | Warning Level " << warningLevel << endl;
    int err = MsgSendPulse_r(coid, sched_get_priority_min(0), LIGHT_SYSTEM, warningLevel);
    if(err) {
        /* FIXME: Discuss sane error handling for message infrastructure failure */
      //  LOG_ERROR << "Sending message failed" << endl;
    }
}
