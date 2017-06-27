/*
 * PuckManager.cpp
 *
 *  Created on: 09.06.2017
 *      Author: aca592
 */

#include "PuckManager.h"

#include "logger.h"
#include "logScope.h"

PuckManager::PuckManager(int chid)
	: puckList()
	, nextPuckID(0)
	, chid(chid)
{}

PuckManager::~PuckManager() {
	std::list<PuckContext*>::iterator it = puckList.begin();
	while(it != puckList.end()) {
		LOG_DEBUG <<"[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
		delete *it;					// delete the puck from memory
		it = puckList.erase(it);	// delete the puck from list
	}
}

PuckManager::ManagerReturn PuckManager::newPuck(PuckSignal::PuckType type) {
	LOG_SCOPE;
	ManagerReturn ret;
	ret.actorFlag = true;
	ret.actorSignal = ActorSignal::ACCEPTED_PUCK;
	puckList.push_back(new PuckContext(chid, type, nextPuckID++));
	return ret;
}

void PuckManager::addPuck(PuckContext *puck) {
	LOG_SCOPE;
	puck->setPuckID(nextPuckID++);
	puckList.push_back(puck);
	LOG_DEBUG << "[PuckManager] Size of puckList" << puckList.size() << endl;
}

PuckManager::ManagerReturn PuckManager::process(PuckSignal::Signal signal) {
	LOG_SCOPE;

	ManagerReturn prioReturnVal; // the prioritized return value
	prioReturnVal.speedSignal = PuckSignal::PuckSpeed::FAST;
	prioReturnVal.actorFlag = false;
	prioReturnVal.errorFlag = false;
	prioReturnVal.puckType = nullptr;

	int32_t acceptCounter = 0; // count all accepted signals
	int32_t warningCounter = 0; // count all warnings

#if !machine // machine0
	// check for first interrupt signal - puck must be created
	if(	signal.signalType == PuckSignal::SignalType::INTERRUPT_SIGNAL &&
		signal.interruptSignal == interrupts::interruptSignals::INLET_IN) {

		addPuck(new PuckContext(chid));

		std::list<PuckContext*>::iterator it = puckList.begin();
		while(it != puckList.end()) {
			if((*it)->getCurrentSpeed() > prioReturnVal.speedSignal) { // Check for speed prio
				prioReturnVal.speedSignal = (*it)->getCurrentSpeed();
			}
			it++;
		}

		return prioReturnVal;
	}

	// signal can be passed for speed prio -> every puck should return deny
#endif

	if (signal.signalType != PuckSignal::SignalType::SERIAL_SIGNAL) {
		if(puckList.empty()) {
			prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
			return prioReturnVal;
		}
	}

	// Pass the timer signal to the given puckID
	if(signal.signalType == PuckSignal::SignalType::TIMER_SIGNAL) {
		std::list<PuckContext*>::iterator it = puckList.begin();
		while(it != puckList.end()) {
			if((*it)->getCurrentSpeed() > prioReturnVal.speedSignal) { // Check for speed prio
				prioReturnVal.speedSignal = (*it)->getCurrentSpeed();
			}

			// check for puckID
			uint16_t currentPuckID = (*it)->getPuckID();
			if(currentPuckID == signal.timerSignal.TimerInfo.puckID) {
				// pass the timer signal
				PuckSignal::Return returnVal = (*it)->process(signal);

				// check return value
				if( returnVal.puckReturn == PuckSignal::PuckReturn::SLIDE_FULL) {
					sort.process(returnVal.puckReturn);

					prioReturnVal.actorFlag = true;
					prioReturnVal.actorSignal = ActorSignal::SEND_SLIDE_FULL;
					if(puckList.size() == 1) {
						prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
					}
				} else if(	returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT &&
					returnVal.puckReturn != PuckSignal::PuckReturn::ERROR) {
					// puck should be triggered on accept or error -> unexpected otherwise
					prioReturnVal.errorFlag = true;
					prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
				} else if(returnVal.puckReturn == PuckSignal::PuckReturn::ERROR) {
					prioReturnVal.errorFlag = true;
					prioReturnVal.errorSignal = ErrorSignal::PUCK_LOST; //Late Timer expiered
				}
			}

			it++;
		}

		LOG_DEBUG << "[PuckManager] Returning with with timer management only \n";
		return prioReturnVal;
	}

	if(signal.signalType == PuckSignal::SignalType::SERIAL_SIGNAL && signal.serialSignal == Serial_n::ser_proto_msg::SLIDE_FULL_SER) {
		sort.process(signal.serialSignal);

		std::list<PuckContext*>::iterator it = puckList.begin();
		while(it != puckList.end()) {
			if((*it)->getCurrentSpeed() > prioReturnVal.speedSignal) { // Check for speed prio
				prioReturnVal.speedSignal = (*it)->getCurrentSpeed();
			}
			it++;
		}
		LOG_DEBUG << "[PuckManager] Returning with with Slide management only \n";
		return prioReturnVal;
	}

	// check the signal for every puck in the list
	std::list<PuckContext*>::iterator it = puckList.begin();
	while(it != puckList.end()) {
		PuckSignal::Return returnVal = (*it)->process(signal);

		if(returnVal.puckSpeed > prioReturnVal.speedSignal) { // Check for speed prio
			prioReturnVal.speedSignal = returnVal.puckSpeed;
		}

		switch(returnVal.puckReturn) {
			case PuckSignal::PuckReturn::ACCEPT:
				acceptCounter++;
				break;
			case PuckSignal::PuckReturn::DELETE:
				acceptCounter++;
				LOG_DEBUG <<"[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
				delete *it;					// delete the puck from memory
				it = puckList.erase(it);	// delete the puck from list
				break;
			case PuckSignal::PuckReturn::SEND:
				acceptCounter++;
				prioReturnVal.puckType = new PuckSignal::PuckType((*it)->getType());
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::SEND_PUCK;
				break;
			case PuckSignal::PuckReturn::RECEIVED:
				acceptCounter++;
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::RECEIVED_PUCK;
				break;
			case PuckSignal::PuckReturn::EVALUATE:
				acceptCounter++;
				if(!sort.process((*it)->getType())) {
					prioReturnVal.actorFlag = true;
					prioReturnVal.actorSignal = ActorSignal::OPEN_SWITCH;
				}
				break;
			case PuckSignal::PuckReturn::START_HEIGHT:
				acceptCounter++;
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::START_MEASUREMENT;
				break;
			case PuckSignal::PuckReturn::STOP_HEIGHT:
				acceptCounter++;
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::STOP_MEASUREMENT;
				break;

			case PuckSignal::PuckReturn::SLIDE_EMPTY:
				acceptCounter++;

				sort.process(returnVal.puckReturn);
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::SEND_SLIDE_EMPTY;
				LOG_DEBUG <<"[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
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
				LOG_DEBUG << "[PuckManager] Returning with Default UNEXPECTED_SIGNAL";
				return prioReturnVal;
		}

		if(		returnVal.puckReturn != PuckSignal::PuckReturn::DELETE ||
				returnVal.puckReturn != PuckSignal::PuckReturn::SLIDE_FULL) {
			++it;
		}
	}

	// metal detect hot fix
	if(signal.signalType == PuckSignal::SignalType::INTERRUPT_SIGNAL
			&& signal.interruptSignal == interrupts::interruptSignals::METAL_DETECT
			&& acceptCounter == 0) {
		prioReturnVal.errorFlag = false;
		acceptCounter++;
	}

	/* Accept serial RESUME and STOP signals */
	if ( signal.signalType == PuckSignal::SignalType::SERIAL_SIGNAL
			&& ( signal.serialSignal == Serial_n::ser_proto_msg::STOP_SER
					|| signal.serialSignal == Serial_n::ser_proto_msg::RESUME_SER )
					&& acceptCounter == 0 ) {
		prioReturnVal.errorFlag = false;
		acceptCounter++;

		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
		std::list<PuckContext*>::iterator it = puckList.begin();
		while(it != puckList.end()) {
			if((*it)->getCurrentSpeed() > prioReturnVal.speedSignal) { // Check for speed prio
				prioReturnVal.speedSignal = (*it)->getCurrentSpeed();
			}
			it++;
		}
	}

	if(!prioReturnVal.errorFlag) {
		if(acceptCounter > 1 || acceptCounter < 0) {
			LOG_DEBUG << "[PuckManager] Returning with MULTIPLE_ACCEPT";
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_ACCEPT;
			return prioReturnVal;
		}

		if(acceptCounter == 0) {
			LOG_DEBUG << "[PuckManager] Returning with UNEXPECTED_SIGNAL";
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
			return prioReturnVal;
		}

		// acceptCounter == 1
		/*if(warningCounter > 1 || warningCounter < 0) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_WARNING;
			return prioReturnVal;
		}*/

		// warning can be ignored
	}

	if(puckList.empty()) {
		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
	}

	LOG_DEBUG << "Puck Manager returns: Speed " << prioReturnVal.speedSignal << " Actor Flag " << prioReturnVal.actorFlag
			 << " Actor Signal " << prioReturnVal.actorSignal << " Error Flag " << prioReturnVal.errorFlag
			 << " Error Signal " << prioReturnVal.errorSignal << " \n";

	// everything OK
	return prioReturnVal;
}
