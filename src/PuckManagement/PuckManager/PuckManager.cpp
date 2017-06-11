/*
 * PuckManager.cpp
 *
 *  Created on: 09.06.2017
 *      Author: aca592
 */

#include "PuckManager.h"

PuckManager::PuckManager() {
	// TODO Auto-generated constructor stub
}

PuckManager::~PuckManager() {
	// TODO Auto-generated destructor stub
}

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

	// TODO: Pass timer signals to puck with puckid
	if(signal.signalType == PuckSignal::SignalType::TIMER_SIGNAL) {
		std::list<PuckContext*>::iterator it = puckList.begin();
		do {
			uint16_t currentPuckID = (*it)->getPuckID();
			if(currentPuckID == signal.timerSignal.puckID) {
				PuckSignal::Return returnVal = (*it)->process(signal);

				switch(returnVal.puckReturn) {
					case PuckSignal::PuckReturn::ACCEPT:

						break;
					case PuckSignal::PuckReturn::DELETE:

						delete *it;					// delete the puck from memory
						it = puckList.erase(it);	// delete the puck from list
						break;
					case PuckSignal::PuckReturn::SEND:

						prioReturnVal.puck = (*it);
						prioReturnVal.actorFlag = true;
						prioReturnVal.actorSignal = ActorSignal::SEND_PUCK;
						break;
					case PuckSignal::PuckReturn::EVALUATE:

						// todo: sort
						break;
					case PuckSignal::PuckReturn::HEIGHT:

						prioReturnVal.actorFlag = true;
						prioReturnVal.actorSignal = ActorSignal::START_MEASUREMENT;
						break;
					case PuckSignal::PuckReturn::SLIDE_FULL:

						prioReturnVal.slideFullFlag = true;
						break;
					//
					case PuckSignal::PuckReturn::WARNING:

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
			}
		} while (it != puckList.end());

		return prioReturnVal;
	}


	int32_t acceptCounter = 0; // count all accepted signals
	int32_t warningCounter = 0; // count all warnings

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

		if(returnVal.puckReturn != PuckSignal::PuckReturn::DELETE) {
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
