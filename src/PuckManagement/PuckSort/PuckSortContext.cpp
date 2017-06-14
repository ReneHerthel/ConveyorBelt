/*!
 * @file PuckSortContext.cpp
 * @brief
 *
 * @author Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 * @internal
 * Created 06/09/2017 05:11:22 PM
 * Copyright  Copyright (c) 2017 Stephan Jänecke
 *
 */

#include "PuckSortContext.h"

/* TODO: Get machine and ramp status */
/* TODO: Process signals */

PuckSortContext::PuckSortContext()
{
	LOG_SCOPE;
	statePtr = &startState;
#if MACHINE
	isOnMachine1 = false;
	isOnMachine2 = true;
#else
	statePtr->isOnMachine1 = true;
	statePtr->isOnMachine2 = false;
#endif
	statePtr->rampe1IsEmpty = true;
	statePtr->rampe2IsEmpty = true;
	statePtr->returnValue = false;
}

/* Decide between PuckType and SlideFull */

/* PuckType */
bool PuckSortContext::process(PuckType signal) {
	LOG_SCOPE;
#if FIFO_SORT
    /* Keep all pucks for now */
    return false;
#else
	LOG_DEBUG << "process: Got " << signal.heightType.ID << endl;
    switch (signal.heightType.ID) {
    case NORMAL_ID:
    	LOG_DEBUG << "process: Got metal = " << signal.metal << endl;
    	if (signal.metal) {
    	    	statePtr->holeWithMetal();
    	} else {
    	    	statePtr->holeWithoutMetal();
    	}
    	break;
    case FLIPPED_ID:
    	statePtr->flipped();
    	break;
    case INVALID_ID:
    	statePtr->lowHeight();
    	break;
    case PATTERN_ID:
    	LOG_DEBUG << "process: : Got pattern " << signal.heightType.BIT2 << signal.heightType.BIT1 << signal.heightType.BIT0 << endl;
    	if (!signal.heightType.BIT2 && !signal.heightType.BIT1 && signal.heightType.BIT0) {
    		// 001
    		statePtr->bitCode1();
    	}

    	if (!signal.heightType.BIT2 && signal.heightType.BIT1 && !signal.heightType.BIT0) {
    		// 010
    		statePtr->bitCode2();
    	}

    	if (signal.heightType.BIT2 && !signal.heightType.BIT1 && !signal.heightType.BIT0) {
    		// 100
    		statePtr->bitCode4();
    	}

    	if (signal.heightType.BIT2 && !signal.heightType.BIT1 && !signal.heightType.BIT0) {
    	    // 101
    	    statePtr->bitCode5();
    	}
    	break;
    default:
    	LOG_DEBUG << "process: Invalid" << endl;
    	statePtr->invalid();
    }
    return statePtr->returnValue;
#endif
}

/* SlideFull */
void PuckSortContext::process(PuckReturn message) {
	if (SLIDE_FULL == message) {
	#if MACHINE
			statePtr->rampe2IsEmpty = false;
	#else
			statePtr->rampe1IsEmpty = false;
	#endif
		}
}

/* SLIDE_FULL_SER */
void PuckSortContext::process(Serial_n::ser_proto_msg message) {
	if (SLIDE_FULL_VAL == message) {
#if MACHINE
		/* FIXME: Probably unnecessary */
		statePtr->rampe1IsEmpty = false;
#else
		statePtr->rampe2IsEmpty = false;
#endif
	}
}


/* Define default transitions */
void PuckSortContext::PuckSort::bitCode1() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::bitCode2() {
	LOG_SCOPE;

	if (isOnMachine2) {
		returnValue = true;
	} else if (rampe2IsEmpty && isOnMachine1) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::bitCode4() {
	LOG_SCOPE;

	if (isOnMachine2) {
		returnValue = true;
	} else if (rampe2IsEmpty && isOnMachine1) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::bitCode5() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::flipped() {
	LOG_SCOPE;
	if (isOnMachine2) {
		returnValue = true;
	} else if (rampe2IsEmpty && isOnMachine1) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::lowHeight() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::holeWithMetal() {
	LOG_SCOPE;
	returnValue = true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}
void PuckSortContext::PuckSort::invalid() {
	LOG_SCOPE;
	returnValue = true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: " << returnValue << endl;
}

/* Define transitions for Start state */
void PuckSortContext::Start::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[Start]->[GotHoleUpWoMetal] Discard: " << returnValue << endl;
	new (this) GotHoleUpMetal;
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
