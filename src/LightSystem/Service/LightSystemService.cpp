// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

void LightSystemService::setWarningLevel(Level warningLevel) {
	// Send light color and frequency to Controller
	Color COLOR;
	Frequency FREQUENCY;

    switch (warningLevel) {
    case OPERATING:
    	COLOR = GREEN;
    	FREQUENCY = ALWAYS_ON;
    	break;
    case NOT_OPERATING:
    	COLOR = GREEN;
    	FREQUENCY = ALWAYS_OFF;
    	break;
    case WARNING:
    	COLOR = YELLOW;
    	FREQUENCY = SLOW_BLINKING; // FIXME: Specify frequency
    	break;
    case CLEAR_WARNING:
    	COLOR = YELLOW;
    	FREQUENCY = SLOW_BLINKING;
    	break;
    case CLEAR_ERROR:
    	COLOR = RED;
    	FREQUENCY = ALWAYS_OFF;
    	break;
    case ERROR_OCCURED:
    	COLOR = RED;
    	FREQUENCY = FAST_BLINKING;
    	break;
    case ERROR_ACKNOWLEDGED:
    	COLOR = RED;
    	FREQUENCY = ALWAYS_ON;
    	break;
    case ERROR_GONE_UNACKNOWLEDGED:
    	COLOR = RED;
    	FREQUENCY = SLOW_BLINKING;
    	break;
    case CLEAR_ALL:
    	COLOR = ALL;
    	FREQUENCY = ALWAYS_OFF;
    	break;
    default:
    	// TODO: Specify default case
    }

    //controller->setLights(COLOR, FREQUENCY); // FIXME: Replace by pulse message send
    //res = MsgSendPulse ( coid, priority, code, value ) ;
}

