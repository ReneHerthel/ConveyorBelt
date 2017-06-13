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
: rampe1IsEmpty(true)
, rampe2IsEmpty(true)
, returnValue(false)
{
#if MACHINE
	isOnMachine1 = false;
	isOnMachine2 = true;
#else
	isOnMachine1 = true;
	isOnMachine2 = false;
#endif
}

/* Decide between PuckType and SlideFull */

/* PuckType */
bool PuckSortContext::process(PuckType signal) {
	LOG_SCOPE;
#if FIFO_SORT
    /* Keep all pucks for now */
    return false;
#else

    switch(signal) {


    }
    return false;
#endif
}

/* SlideFull */
void PuckSortContext::process(PuckReturn message) {

}

/* Define default transitions */
void PuckSortContext::PuckSort::bitCode1() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
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

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
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

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}
void PuckSortContext::PuckSort::bitCode5() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}
void PuckSortContext::PuckSort::flipped() {
	LOG_SCOPE;

	LOG_SCOPE;

	if (isOnMachine2) {
		returnValue = true;
	} else if (rampe2IsEmpty && isOnMachine1) {
		returnValue = true;
	} else {
		returnValue = false;
	}

	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}
void PuckSortContext::PuckSort::lowHeight() {
	LOG_SCOPE;
	returnValue = (rampe1IsEmpty && isOnMachine1) ? false : true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}
void PuckSortContext::PuckSort::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}
void PuckSortContext::PuckSort::holeWithMetal() {
	LOG_SCOPE;
	returnValue = true;
	LOG_DEBUG << "[PuckSort]->[PuckSort] Discard: \n" << returnValue;
}

/* Define transitions for Start state */
void PuckSortContext::Start::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[Start]->[GotHoleUpWoMetal] Discard: \n" << returnValue;
	new (this) GotHoleUpMetal;
}

/* Define transitions for GotHoleUpWoMetal state */
void PuckSortContext::GotHoleUpWoMetal::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[GotHoleUpWoMetal]->[GotTwoHoleUpWoMetal] Discard: \n" << returnValue;
	new (this) GotTwoHoleUpMetal;
}

/* Define transitions for GotTwoHoleUpWoMetal state */
void PuckSortContext::GotTwoHoleUpWoMetal::holeWithoutMetal() {
	LOG_SCOPE;
	returnValue = false;
	LOG_DEBUG << "[GotTwoHoleUpWoMetal]->[GotHoleUpMetal] Discard: \n" << returnValue;
	new (this) GotHoleUpMetal;
}
