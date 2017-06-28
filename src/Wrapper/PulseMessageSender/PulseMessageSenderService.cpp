/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    wrapper
 * @{
 *
 * @brief      Function declaration of the PulseMessageSenderService.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "PulseMessageSenderService.h"

#include "Logger.h"
#include "LogScope.h"


#include <sys/netmgr.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>

PulseMessageSenderService::PulseMessageSenderService(const int chid)
    :    chid_(chid)
{
    // Try to connect to the given channel ID.
    int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, chid, 0, 0);

    // Check if there occurs an error.
    if (coid < 0) {
        // TODO: Error handling.
        LOG_ERROR << "[PulseMessageSenderService] PulseMessageSenderService() An error occurs on ConnectAttach_r [" << coid << "]\n";
    }

    // Remember the coid for the whole object.
    coid_ = coid;
}

void PulseMessageSenderService::sendPulseMessage(const int code, const int value)
{
    // Check if there is a valid connection ID.
    if (coid_ < 0) {
        // TODO: Error handling.
        LOG_ERROR << "[PulseMessageSenderService] sendPulseMessage() The coid is identified as error [" << coid_ << "], exit method.\n";
        return;
    }

    // Try to send a pulse message with the given 32-bit value over the connection ID.
    int err = MsgSendPulse_r(coid_, sched_get_priority_min(0), code, value);

    // Check if an error occurs on MsgSendPulse_r.
    if (err < 0) {
        // TODO: Error handling.
        LOG_ERROR << "[PulseMessageSenderService] sendPulseMessage() Error occurs on MsgSendPulse_r [" << err << "]\n";
    }
}

void PulseMessageSenderService::sendPulseMessage(struct _pulse p)
{
    // Check if there is a valid connection ID.
    if (coid_ < 0) {
        // TODO: Error handling.
        LOG_ERROR << "[PulseMessageSenderService] sendPulseMessage() The coid is identified as error [" << coid_ << "], exit method.\n";
        return;
    }

    // Try to send a pulse message with the given 32-bit value over the connection ID.
    int err = MsgSendPulse_r(coid_, sched_get_priority_min(0), p.code, p.value.sival_int);

    // Check if an error occurs on MsgSendPulse_r.
    if (err < 0) {
        // TODO: Error handling.
        LOG_ERROR << "[PulseMessageSenderService] sendPulseMessage() Error occurs on MsgSendPulse_r [" << err << "]\n";
    }
}

/** @} */
