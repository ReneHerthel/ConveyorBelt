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
 * @brief      Interface declaration of the PulseMessageReceiver.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_WRAPPER_PULSEMESSAGERECEIVER_IPULSEMESSAGERECEIVER_H_
#define SRC_WRAPPER_PULSEMESSAGERECEIVER_IPULSEMESSAGERECEIVER_H_

namespace rcv {

/*
 * @brief The struct for some of the received pulse message values.
 */
typedef struct {
    int code;
    int value;
} msg_t ;

class IPulseMessageReceiver
{
public:
    /*
     * @brief Returns the 32-bit value of an incoming pulse message.
     *
     * @return A 32-bit value from the pulse message on success.
     *         The error-codes from MsgReceive_r and ChannelCreate_r on failure.
     */
    virtual msg_t receivePulseMessage() = 0;

    /*
     * @brief Creates a new channel.
     *
     * @return The new channel identifier.
     */
    virtual int newChannel() = 0;
};

} /* namespace rcv */

#endif /* SRC_WRAPPER_PULSEMESSAGERECEIVER_IPULSEMESSAGERECEIVER_H_ */
/** @} */
