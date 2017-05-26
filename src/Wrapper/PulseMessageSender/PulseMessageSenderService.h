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
 * @brief      Header declaration of the PulseMessageSenderService.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_WRAPPER_PULSEMESSAGESENDER_PULSEMESSAGESENDERSERVICE_H_
#define SRC_WRAPPER_PULSEMESSAGESENDER_PULSEMESSAGESENDERSERVICE_H_

#include "IPulseMessageSender.h"

class PulseMessageSenderService : public IPulseMessageSender
{
public:
    /*
     * @brief Constructor with a channel ID.
     *
     * @param [chid] The channel ID, where this object will make a connection to.
     */
    PulseMessageSenderService(const int chid);

    /*
     * @brief Transmit a pulse message to a given connection ID.
     *
     * @param[value] A 32-bit value for the pulse message.
     */
    void sendPulseMessage(const int value);

private:
    /*
     * @brief The channel ID, where this object will make a connection to.
     */
    int chid_;

    /*
     * @brief The connection ID, where the pulse messages will be sent to.
     */
    int coid_;
};

#endif /* SRC_WRAPPER_PULSEMESSAGESENDER_PULSEMESSAGESENDERSERVICE_H_ */
/** @} */
