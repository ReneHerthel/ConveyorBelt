// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

LightSystemService::LightSystemService(int chid, LightSystemController* controller):
    chid(chid)
	, controller(controller)
{};

void LightSystemService::setWarningLevel(Level warningLevel) {
	LOG_SCOPE;
    /* FIXME: Discuss Priorities */
    /* 80 is ID for lightSystem */
	 static const LightMessage LightMessageMapping[] = {
		            { GREEN, ALWAYS_ON }, // OPERATING
		            { GREEN, ALWAYS_OFF }, // NOT_OPERATING
		            { YELLOW, SLOW_BLINKING }, // WARNING_OCCURED
		            { YELLOW, ALWAYS_OFF }, // CLEAR_WARNING
		            { RED, ALWAYS_OFF }, // CLEAR_ERROR
		            { RED, FAST_BLINKING }, // ERROR_OCCURED
		            { RED, ALWAYS_ON }, // ERROR_ACKNOWLEDGED
		            { RED, SLOW_BLINKING }, // ERROR_GONE_UNACKNOWLEDGED
		            { ALL, ALWAYS_OFF } // CLEAR_ALL
		    };

		    controller->color = LightMessageMapping[warningLevel].color;
		    LOG_DEBUG << "Set color: " << controller->color << endl;
		    controller->frequency = LightMessageMapping[warningLevel].frequency;
		    LOG_DEBUG << "Set frequency: " << controller->frequency << endl;
}
