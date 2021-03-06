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

 #ifndef SRC_EXAMPLES_WRAPPER_THREADSERVER_H
 #define SRC_EXAMPLES_WRAPPER_THREADSERVER_H

#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"

#include <thread>
#include <sys/netmgr.h>
#include <sys/siginfo.h>
#include <iostream>

class ThreadServer
{
public:
    /*
     * @brief Constructor with channel ID.
     *
     * @param[chid] The channel ID, to receive pulse messages from.
     */
    ThreadServer(const int chid);

    /*
     * @brief Default destructor.
     */
    ~ThreadServer();

    /*
     * @brief waits if the thread has a message received.
     */
    rcv::msg_t receivePulseMessage();

private:

    /*
     * @brief The channel ID, where the server will receive pulse messages.
     */
    int chid_;

    /*
     * @brief The Server thread.
     */
    std::thread server_t;

    /*
     * @brief Receives a pulse message in the thread
     */
    void receive();

    /*
     * @brief To poll if the message was received by the thread.
     */
    bool messageReceived_;

    /*
     * @brief The value of the pulse message.
     */
    rcv::msg_t pulseMessageValue_;
};

 #endif /* SRC_EXAMPLES_WRAPPER_THREADSERVER_H */

 /** @} */
