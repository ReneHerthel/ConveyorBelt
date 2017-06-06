/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    led
 * @{
 *
 * @brief      Hal function declaration of the LED component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "LedHal.h"
#include "HWaccess.h"
#include "HWdefines.h"
#include "Port.h"

LedHal::LedHal(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	// Nothing to do so far.
}

void LedHal::set() {
	out8(port_, (in8(port_) | (1 << pin_)));
}

void LedHal::clear() {
	out8(port_, (in8(port_) & ~(1 << pin_)));
}

/** @} */
