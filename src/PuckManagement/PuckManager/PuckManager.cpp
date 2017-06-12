/*
 * PuckManager.cpp
 *
 *  Created on: 09.06.2017
 *      Author: aca592
 */

#include "PuckManager.h"

PuckManager::PuckManager()
	: puckList()
	, nextPuckID(0)
{}

void PuckManager::addPuck(PuckContext *puck) {
	puck->setPuckID(nextPuckID++);
	puckList.push_back(puck);
}

PuckManager::ManagerReturn PuckManager::process(PuckSignal::Signal signal) {
	ManagerReturn prioReturnVal; // the prioritized return value
	prioReturnVal.puckSpeed = PuckSignal::PuckSpeed::FAST;
	prioReturnVal.actorFlag = false;
	prioReturnVal.errorFlag = false;
	prioReturnVal.slideFullFlag = false;
	prioReturnVal.puck = nullptr;

	int32_t acceptCounter = 0; // count all accepted signals
	int32_t warningCounter = 0; // count all warnings

#if !machine // machine0
	// check for first interrupt signal - puck must be created
	if(	signal.signalType == PuckSignal::SignalType::INTERRUPT_SIGNAL &&
		signal.interruptSignal == interrupts::interruptSignals::INLET_IN) {

		addPuck(new PuckContext());
		acceptCounter++; // accept the signal manually
	}

	// signal can be passed for speed prio -> every puck should return deny
#endif

	// Pass the timer signal to the given puckID
	if(signal.signalType == PuckSignal::SignalType::TIMER_SIGNAL) {
		std::list<PuckContext*>::iterator it = puckList.begin();
		do {
			if((*it)->getCurrentSpeed() > prioReturnVal.puckSpeed) { // Check for speed prio
				prioReturnVal.puckSpeed = (*it)->getCurrentSpeed();
			}

			// check for puckID
			uint16_t currentPuckID = (*it)->getPuckID();
			if(currentPuckID == signal.timerSignal.puckID) {
				// pass the timer signal
				PuckSignal::Return returnVal = (*it)->process(signal);

				// check return value
				if(	returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT &&
					returnVal.puckReturn != PuckSignal::PuckReturn::ERROR) {
					// puck should be triggered on accept or error -> unexpected otherwise
					prioReturnVal.errorFlag = true;
					prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
				} else if(returnVal.puckReturn == PuckSignal::PuckReturn::ERROR) {
					prioReturnVal.errorFlag = true;
					prioReturnVal.errorSignal = ErrorSignal::PUCK_LOST; //Late Timer expiered
				}
			}
		} while (it != puckList.end());

		return prioReturnVal;
	}

	// check the signal for every puck in the list
	std::list<PuckContext*>::iterator it = puckList.begin();
	do {
		PuckSignal::Return returnVal = (*it)->process(signal);

		if(returnVal.puckSpeed > prioReturnVal.puckSpeed) { // Check for speed prio
			prioReturnVal.puckSpeed = returnVal.puckSpeed;
		}

		switch(returnVal.puckReturn) {
			case PuckSignal::PuckReturn::ACCEPT:
				acceptCounter++;
				break;
			case PuckSignal::PuckReturn::DELETE:
				acceptCounter++;
				delete *it;					// delete the puck from memory
				it = puckList.erase(it);	// delete the puck from list
				break;
			case PuckSignal::PuckReturn::SEND:
				acceptCounter++;
				prioReturnVal.puck = (*it);
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::SEND_PUCK;
				break;
			case PuckSignal::PuckReturn::EVALUATE:
				acceptCounter++;
				// todo: sort
				break;
			case PuckSignal::PuckReturn::HEIGHT:
				acceptCounter++;
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::START_MEASUREMENT;
				break;
			case PuckSignal::PuckReturn::SLIDE_FULL:
				acceptCounter++;
				prioReturnVal.slideFullFlag = true;
				delete *it;					// delete the puck from memory
				it = puckList.erase(it);	// delete the puck from list
				break;
			//
			case PuckSignal::PuckReturn::WARNING:
				warningCounter++;
				break;
			case PuckSignal::PuckReturn::DENY:
				break;
			case PuckSignal::PuckReturn::ERROR:
				prioReturnVal.errorFlag = true;
				prioReturnVal.errorSignal = ErrorSignal::PUCK_LOST;
				break;
			default:
				prioReturnVal.errorFlag = true;
				prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
				return prioReturnVal;
		}

		if(		returnVal.puckReturn != PuckSignal::PuckReturn::DELETE ||
				returnVal.puckReturn != PuckSignal::PuckReturn::SLIDE_FULL) {
			++it;
		}
	} while ( it != puckList.end());

	if(!prioReturnVal.errorFlag) {
		if(acceptCounter > 1 || acceptCounter < 0) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_ACCEPT;
			return prioReturnVal;
		}

		if(acceptCount == 0) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
			return prioReturnVal;
		}

		// acceptCounter == 1
		if(warningCounter > 1 || warningCounter < 0) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_WARNING;
			return prioReturnVal;
		}

		// warning can be ignored
	}

	// everything OK
	return prioReturnVal;
}
