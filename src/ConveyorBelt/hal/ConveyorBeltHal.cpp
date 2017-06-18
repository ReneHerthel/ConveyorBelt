/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    conveyor_belt
 * @{
 *
 * @brief      Hal Function declaration of the ConveyorBelt component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ConveyorBeltHal.h"
#include "HWdefines.h"
#include "HWaccess.h"

#include "PortA.h"

void ConveyorBeltHal::setMask(const uint8_t mask)
{
    PortA& portA = PortA::getInstance();
    portA.bitClear(ENGINE_REG_MASK);
	portA.bitSet(mask);
}

/** @} */
