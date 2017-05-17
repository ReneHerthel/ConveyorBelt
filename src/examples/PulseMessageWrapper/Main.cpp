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
#include "ServerClient.h"

#include <sys/neutrino>
#include <chrono>
#include <iostream>

int main(void)
{
    std::cout << "[PulseMessageWrapper] Start" << std::endl;

    // We need to create a new channel to give it to the both threads.
    int chid = ChannelCreate_r(0);

    if (chid < 0) {
        std::cout << "[PulseMessageWrapper] Channel creation failed" << std::endl;
    }

    ThreadServer* server = new Threadserver(chid);

    std::cout << "[PulseMessageWrapper] Server created" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    ThreadClient* client = new ThreadClient(chid);

    std::cout << "[PulseMessageWrapper] Client created" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "[PulseMessageWrapper] Done" << std::endl;

    return 0;
}

/** @} */
