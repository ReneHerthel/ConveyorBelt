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
 * @brief      Header declaration of the PulseMessageReceiverService.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_WRAPPER_PULSEMESSAGERECEIVER_PULSEMESSAGERECEIVERSERVICE_H_
#define SRC_WRAPPER_PULSEMESSAGERECEIVER_PULSEMESSAGERECEIVERSERVICE_H_

#include "IPulseMessageReceiver.h"

class PulseMessageReceiverService : public IPulseMessageReceiver
{
public:
    /*
     * @brief Default constructor.
     *
     * @description NOTE: You need to use the newChannel() method after using
     *                    the default constructor.
     */
    PulseMessageReceiverService();

    /*
     * @brief Constructor, which uses a given channel ID.
     *
     * @param [chid] The channel ID, where this object will receive pulse
     *               messages from.
     */
    PulseMessageReceiverService(const int chid);

    /*
     * @brief Receives a new pulse message.
     *
     * @description NOTE: This function will BLOCK the using thread, until it
     *                    receives a new pulse message.
     *
     * @return A struct of some values from the pulse message on success.
     *         The error-codes from MsgReceive_r and ChannelCreate_r on failure.
     */
    rcv_msg_t receivePulseMessage();

    /*
     * @brief Creates a new channel.
     *
     * @return The new channel identifier.
     */
    int newChannel();

private:
    /*
     * @brief The created or given channel ID, where this object receives
     *        pulse messages.
     */
    int chid_;
};

#endif /* SRC_WRAPPER_PULSEMESSAGERECEIVER_PULSEMESSAGERECEIVERSERVICE_H_ */
/** @} */
