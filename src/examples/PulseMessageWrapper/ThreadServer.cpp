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

#include "ThreadServer.h"

#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"

ThreadServer::ThreadServer(const int chid)
    :    chid_(chid)
{
    // Create a thread on the stack, so it will be killed after his task is done.
    server_t = std::thread(&ThreadServer::sendSinglePulseMessage, this);
}

ThreadServer::~ThreadServer()
{
    // TODO: Kill or delete the thread, when it is on the heap.
}

void ThreadServer::receiveSinglePulseMessage()
{
    std::cout << "[ThreadServer] receiveSinglePulseMessage() Start" << std::endl;

    /* NOTE: If we use the default constructor, we need to call the newChannel()
     *       method, to get a new channel ID, which could be pass around.
     *
     *      IPulseMessageReceiver* receiver = new PulseMessageReceiverService()
     *      int chid =  receiver.newChannel();
     *      // Pass chid around.
     *      int value = receiver.receivePulseMessage();
     *      and so on..
     */
    IPulseMessageReceiver* receiver = new PulseMessageReceiverService(chid_);

    std::cout << "[ThreadServer] receiveSinglePulseMessage() Is Now waiting for a pulse message" << std::endl;

    int value = receiver.receivePulseMessage();

    std::cout << "[ThreadServer] receiveSinglePulseMessage() received value: " << value << std::endl;
}

/** @} */
