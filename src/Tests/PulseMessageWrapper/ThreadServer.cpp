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
    server_t = std::thread(&ThreadServer::receive, this);
}

ThreadServer::~ThreadServer()
{
    //
}

void ThreadServer::receive()
{
    //std::cout << "[ThreadServer] receiveSinglePulseMessage() Start" << std::endl;

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

    //std::cout << "[ThreadServer] receiveSinglePulseMessage() Is Now waiting for a pulse message" << std::endl;

    pulseMessageValue_ = receiver->receivePulseMessage();

    std::cout << "[ThreadServer] receiveSinglePulseMessage() received value: " << pulseMessageValue_ << std::endl;

    messageReceived_ = true;
}

int ThreadServer::receivePulseMessage()
{
	// This is just for the test so we dont need to sync with the main.
    while (!messageReceived_) {
    	// Just wait.
    }

    return pulseMessageValue_;
}



/** @} */
