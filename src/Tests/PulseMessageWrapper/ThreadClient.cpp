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

#include <iostream>

ThreadClient::ThreadClient(const int chid, int mod)
    :    chid_(chid)
{
    // quick and dirty
    if (mod == 1) {
        // Create a thread on the stack, so it will be killed after his task is done.
        client_t = std::thread(&ThreadClient::sendSinglePulseMessage, this);
    }
    else if (mod == 2) {
        // Create a thread on the stack, so it will be killed after his task is done.
        client_t = std::thread(&ThreadClient::sendSingleStruct, this);
    }
}

ThreadClient::~ThreadClient()
{
    // Nothing todo so far.
}

void ThreadClient::sendSinglePulseMessage()
{
    // Creates a new Sender.
    IPulseMessageSender* sender = new PulseMessageSenderService(chid_);

    std::cout << "[ThreadClient] sendSinglePulseMessage() sending now value 42" << std::endl;

    // Transmit a code and value to the channel ID.
    sender->sendPulseMessage(3, 42);
}

void ThreadClient::sendSingleStruct()
{
  struct _pulse pulse;

  // Creates a new Sender.
  IPulseMessageSender* sender = new PulseMessageSenderService(chid_);

  std::cout << "[ThreadClient] sendSinglePulseMessage() sending now value 42" << std::endl;

  pulse.code = 4;
  pulse.value.sival_int = 55;

  // Transmit a pulse message to the channel ID.
  sender->sendPulseMessage(pulse);
}

/** @} */
