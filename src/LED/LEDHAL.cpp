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
* @brief      Function declaration of the LED component
*
* @author     Rene Herthel <rene.herthel@haw-hamburg.de>
*/

#include "LEDHAL.h"
#include "HWaddresses.h"
#include "HWaccess.h"
#include <iostream>

LEDHAL::LEDHAL(const int port, const int pin)
	: port_(port)
	, pin_(pin)
{
	unsigned char tmp = in8(CTRL_REG_GROUP0);
	out8(port_, DEFAULT_PORT_SETTINGS);
}

LEDHAL::~LEDHAL() {
	// Nothing todo so far.
}

void LEDHAL::on() {
	unsigned char tmp = in8(port_);
	out8(port_, (tmp | (1 << pin_)));
}

void LEDHAL::off() {
	unsigned char tmp = in8(port_);
	out8(port_, (tmp & ~(1 << pin_)));
}

/** @} */
