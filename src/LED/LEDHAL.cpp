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

#include "LEDHal.h"
#include "HWaddresses.h"
#include "HWaccess.h"
#include <iostream>

#define PORTPIN_MASK 0x0F

BLED::~BLED() {
	// Nothing todo so far.
}

LEDHal::LEDHal(const int ledPinMask)
	: ledPinMask_(ledPinMask)
{
	// Nothing todo so far.
}

LEDHal::~LEDHal(){
	// Nothing todo so far.
}

void LEDHal::on() {
	out8(PORTC_REG_ADDR, (in8(PORTC_REG_ADDR) | ledPinMask_));
}

void LEDHal::off() {
	out8(PORTC_REG_ADDR, (in8(PORTC_REG_ADDR) & ~ledPinMask_));
}

int LEDHal::read() {
	return in8(PORTC_REG_ADDR) & (PORTPIN_MASK | ledPinMask_);
}

/** @} */
