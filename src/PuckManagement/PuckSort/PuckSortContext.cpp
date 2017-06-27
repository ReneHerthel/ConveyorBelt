/*!
 *    \file  PuckSortContext.cpp
 *   \brief  Implements the PuckSort state machine
 *
 *  Decides if the given puck will be discarded or not. Pucks of the
 *  sequence defined in the specialized states will be passed on. There
 *  are standard actions defined in the super state performed on other
 *  pucks and pucks out of sequence.
 *
 *  When ENABLE_FIFO_SORT is set, no sorting will happen and all pucks
 *  will be passed. If VARIANT_Belt0 is set the machine will execute
 *  the specific algorithm for machine 0.
 *
 *  \author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *  \internal
 *       Created:  06/09/2017
 * Last modified:  06/21/2017
 *     Copyright:  Copyright (c) 2017 Stephan Jänecke licensed under the
 *     MIT License
 */

#include "PuckSortContext.h"

using namespace PuckSignal;
using namespace HeightMeasurement;

PuckSortContext::PuckSortContext()
{
	LOG_SCOPE;
	statePtr = &startState;

#ifdef VARIANT_Belt0
	statePtr->isOnMachine0 = true;
	statePtr->isOnMachine1 = false;
#else
	statePtr->isOnMachine0 = false;
	statePtr->isOnMachine1 = true;
#endif
	statePtr->slide0IsEmpty = true;
	statePtr->slide1IsEmpty = true;
	statePtr->returnValue = false;
}

/* Decide between PuckType and SlideFull */

/* PuckType */
bool PuckSortContext::process(PuckType signal) {
	LOG_SCOPE;
#ifdef ENABLE_FIFO_SORT /*!< \brief If set, disables sort algorithm and let all pucks pass */
    /* Keep all pucks for now */
    return false;
#else
    switch (signal.data.heightType.ID) {
    case NORMAL_ID:
    	LOG_DEBUG << "process: Got metal = " <<  int(signal.data.metal) << endl;
    	if (signal.data.metal) {
    			LOG_DEBUG << "process: Got METAL" << endl;
    	    	statePtr->holeWithMetal();
    	} else {
			LOG_DEBUG << "process: Got NORMAL" << endl;
    	    	statePtr->holeWithoutMetal();
    	}
    	break;
    case FLIPPED_ID:
		LOG_DEBUG << "process: Got FLIPPED" << endl;
    	statePtr->flipped();
    	break;
    case PATTERN_ID:
    	LOG_DEBUG << "process: Got pattern " << int(signal.data.heightType.BIT2) << int(signal.data.heightType.BIT1) << int(signal.data.heightType.BIT0) << endl;
    	if (!signal.data.heightType.BIT2 && !signal.data.heightType.BIT1 && signal.data.heightType.BIT0) {
    		// 001
    		LOG_DEBUG << "process: Got BITCODE1" << endl;
    		statePtr->bitCode1();
    	}

    	if (!signal.data.heightType.BIT2 && signal.data.heightType.BIT1 && !signal.data.heightType.BIT0) {
    		// 010
    		LOG_DEBUG << "process: Got BITCODE2" << endl;
    		statePtr->bitCode2();
    	}

    	if (signal.data.heightType.BIT2 && !signal.data.heightType.BIT1 && !signal.data.heightType.BIT0) {
    		// 100
    		LOG_DEBUG << "process: Got BITCODE4" << endl;
    		statePtr->bitCode4();
    	}

    	if (signal.data.heightType.BIT2 && !signal.data.heightType.BIT1 && signal.data.heightType.BIT0) {
    	    // 101
    		LOG_DEBUG << "process: Got BITCODE5" << endl;
    	    statePtr->bitCode5();
    	}
    	break;
    default:
    	LOG_DEBUG << "process: Invalid" << endl;
    	statePtr->invalid();
    }
    LOG_DEBUG << "process: Return " << statePtr->returnValue << endl;
    return statePtr->returnValue;
#endif
}

/* Slide */
void PuckSortContext::process(PuckReturn message) {
	switch (message) {
	case SLIDE_FULL:
#ifdef VARIANT_Belt0
		statePtr->slide0IsEmpty = false;
#else
		statePtr->slide1IsEmpty = false;
#endif
		break;
	case SLIDE_EMPTY:
#ifdef VARIANT_Belt0
		statePtr->slide0IsEmpty = true;
#else
		statePtr->slide1IsEmpty = true;
#endif
		break;
	default:
		/* Ignore unhandled messages */
		;
	};
}

/* SLIDE_SER */
void PuckSortContext::process(Serial_n::ser_proto_msg message) {

	switch (message) {
	case Serial_n::SLIDE_FULL_SER:
#ifdef VARIANT_Belt0
		statePtr->slide1IsEmpty = false;
#else
		statePtr->slide0IsEmpty = false;
#endif
		break;
	case Serial_n::SLIDE_EMTPY_SER:
#ifdef VARIANT_Belt0
		statePtr->slide1IsEmpty = true;
#else
		statePtr->slide0IsEmpty = true;
#endif
		break;
	default:
		/* Ignore unhandled messages */
		;
	};
}

void PuckSortContext::PuckSort::logConditionals(void) {
	LOG_DEBUG << "[PuckSortContext] rampe0IsEmpty: " << int(slide0IsEmpty) << " rampe1IsEmpty: " <<  int(slide1IsEmpty)
			<< " isOnMachine0: " << int(isOnMachine0) << " isOnMachine1: " << int(isOnMachine1) << endl;
}

/* Define default transitions */
void PuckSortContext::PuckSort::bitCode1() {
	LOG_SCOPE;
	if ( slide0IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::bitCode2() {
	LOG_SCOPE;

	if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else if ( !slide1IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::bitCode4() {
	LOG_SCOPE;

	if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else if (!slide1IsEmpty && isOnMachine0) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::bitCode5() {
	LOG_SCOPE;
	if ( slide0IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::flipped() {
	LOG_SCOPE;
	if ( slide0IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::holeWithoutMetal() {
	LOG_SCOPE;
	if ( !slide1IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::holeWithMetal() {
	LOG_SCOPE;
	if ( !slide1IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}
void PuckSortContext::PuckSort::invalid() {
	LOG_SCOPE;
	if ( slide0IsEmpty && isOnMachine0 ) {
		returnValue = true;
	} else if ( slide1IsEmpty && isOnMachine1 ) {
		returnValue = true;
	} else {
		returnValue = false;
	}
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
	logConditionals();
}

/* Define transitions for Start state */
void PuckSortContext::Start::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[Start]->[GotHoleUpWoMetal] Discard: " << returnValue << endl;
	new (this) GotHoleUpWoMetal;
}

/* Define transitions for GotHoleUpWoMetal state */
void PuckSortContext::GotHoleUpWoMetal::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[GotHoleUpWoMetal]->[GotTwoHoleUpWoMetal] Discard: " << returnValue << endl;
	new (this) GotTwoHoleUpWoMetal;
}

/* Define transitions for GotTwoHoleUpWoMetal state */
void PuckSortContext::GotTwoHoleUpWoMetal::holeWithMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[GotTwoHoleUpWoMetal]->[GotHoleUpMetal] Discard: " << returnValue << endl;
	new (this) GotHoleUpMetal;
}
