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

#ifndef SRC_EXAMPLES_WRAPPER_THREADCLIENT_H_
#define SRC_EXAMPLES_WRAPPER_THREADCLIENT_H_

#include "IPulseMessageSender.h"
#include "PulseMessageSenderService.h"

#include <thread>
#include <sys/netmgr.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <iostream>

class ThreadClient
{
public:
    /*
     * @brief Constructor with channel ID.
     *
     * @param[chid] The channel ID, where the client will send to.
     */
    ThreadClient(const int chid);

    /*
     * @brief Default destructor.
     */
    ~ThreadClient();

private:
    /*
     * @brief Transmit a single pulse message to the channel id.
     */
    void sendSinglePulseMessage();

    /*
     * @brief The channel ID, where the client will send to.
     */
    int chid_;

    /*
     * @brief The client thread.
     */
    std::thread client_t;
};

#endif /* SRC_EXAMPLES_WRAPPER_THREADCLIENT_H_ */
/** @} */
