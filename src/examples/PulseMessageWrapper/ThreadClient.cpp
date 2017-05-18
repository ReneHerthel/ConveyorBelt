/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    example
 * @{
 *
 * @brief      Example application for the PulseMessageReceiver/Sender.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ThreadClient.h"

#include "IPulseMessageSender.h"
#include "PulseMessageSenderService.h"

ThreadClient::ThreadClient(const int chid)
    :    chid_(chid)
{
    // Create a thread on the stack, so it will be killed after his task is done.
    client_t = std::thread(&ThreadClient::sendSinglePulseMessage, this);
}

ThreadClient::~ThreadClient()
{
    // TODO: Kill / delete the thread if it is on the heap.
}

void ThreadClient::sendSinglePulseMessage()
{
    // Creates a new Sender.
    IPulseMessageSender* sender = new PulseMessageSenderService(chid_);

    // Transmit a pulse message to the channel ID.
    sender->sendPulseMessage(101010);
}

/** @} */
