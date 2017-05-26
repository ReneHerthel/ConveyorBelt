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
 * @brief      Interface declaration of the PulseMessageSender.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_WRAPPER_PULSEMESSAGESENDER_IPULSEMESSAGESENDER_H_
#define SRC_WRAPPER_PULSEMESSAGESENDER_IPULSEMESSAGESENDER_H_

#include <stdint.h>

class IPulseMessageSender
{
public:
    /*
     * @brief send a pulse message to a given connection ID.
     *
     * @param[code] A 8-bit code value for the pulse message.
     * @param[value] A 32-bit value for the pulse message.
     */
    virtual void sendPulseMessage(const int code, const int value) = 0;
};

#endif /* SRC_WRAPPER_PULSEMESSAGESENDER_IPULSEMESSAGESENDER_H_ */

/** @} */
