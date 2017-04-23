/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Interface declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HEIGHTSTATECONTEXT_H_
#define HEIGHTSTATECONTEXT_H_

include "HeightState.h"

class HeightStateContext : public IHeightMeasurement {
public:

    /*
     * @brief TODO
     */
    void registerToChannel( /* TODO */);

    // TODO declare more interface functionality.

private:

    /*
     * @brief TODO
     */
    HeightState *state;

    /*
     * @brief TODO
     */
    int heightReference;
}

#endif /* HEIGHTSTATECONTEXT_H_ */
/** @} */
