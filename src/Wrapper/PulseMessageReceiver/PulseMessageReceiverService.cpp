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
 * @brief      Function declaration of the PulseMessageReceiverService.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "PulseMessageReceiverService.h"

#include "Logger.h"
#include "LogScope.h"

#include <sys/neutrino.h>

PulseMessageReceiverService::PulseMessageReceiverService()
{
    // Nothing todo so far.
}

PulseMessageReceiverService::PulseMessageReceiverService(const int chid)
    :    chid_(chid)
{
    /* Nothing todo so far.
     * This constructor is just used to initialize PulseMessageReceiverService-
     * objects with an channel ID, without creating a new one.
     */
}

rcv_msg_t PulseMessageReceiverService::receivePulseMessage()
{
    rcv_msg_t receivedMessage;

    // First check if there is a vaild channel ID.
    if (chid_ < 0) {
        LOG_DEBUG << "[PulseMessageReceiverService] receivePulseMessage() chid was an error [" << chid_ << "]\n";
        return chid_;
    }

    // The struct that defines a pulse.
    struct _pulse pulse;

    // Blocks and wait for an incoming pulse message.
    int err = MsgReceive_r(chid_, &pulse, sizeof(_pulse), NULL);

    // Check if an error occurs from the MsgReceive_r function.
    if (err < 0) {
        // TODO: Error handling.
        LOG_DEBUG << "[PulseMessageReceiverService] receivePulseMessage() Error occurs on MsgReceive_r [" << err << "]\n";
        return err;
    }

    // Extract the code and sival_int from the received pulse message.
    receivedMessage.code = pulse.code;
    receivedMessage.value = pulse.value.sival_int;

    return receivedMessage;
}

int PulseMessageReceiverService::newChannel()
{
    // Create a new channel for this object.
    int chid = ChannelCreate_r(0);

    // Log if there occures an error.
    if (chid < 0) {
        LOG_DEBUG << "[PulseMessageReceiverService] PulseMessageReceiverService() Channel creation failed\n";
    }

    // Remember the channel ID for the whole object.
    chid_ = chid;

    // Returns the channel ID.
    return chid_;
}

 /** @} */
