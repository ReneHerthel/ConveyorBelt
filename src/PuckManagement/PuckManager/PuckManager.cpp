/*
 * PuckManager.cpp
 *
 *  Created on: 09.06.2017
 *      Author: aca592
 */

#include "PuckManager.h"

#include "logger.h"
#include "logscope.h"

serialized PuckManager::serialize() {
    serialized ser;
    ser.size = 0;
    ser.obj = nullptr;

    return ser;
}

bool PuckManager::deserialize(void *ser) {
    PuckSignal::PuckType type = *((PuckSignal::PuckType*)ser);
    PuckContext *puck = new PuckContext(chid, type);
    addPuck(puck);

	return true;
}

PuckManager::PuckManager(int chid)
	: puckList()
	, nextPuckID(0)
	, chid(chid)
{}

PuckManager::~PuckManager() {
	std::list<PuckContext*>::iterator it = puckList.begin();
	while(it != puckList.end()) {
		delete *it;					// delete the puck from memory
		it = puckList.erase(it);	// delete the puck from list
	}
}

void PuckManager::addPuck(PuckContext *puck) {
	LOG_SCOPE;
	puck->setPuckID(nextPuckID++);
	puckList.push_back(puck);
}

PuckManager::ManagerReturn PuckManager::process(PuckSignal::Signal signal) {
	LOG_SCOPE;

	ManagerReturn prioReturnVal; // the prioritized return value
	prioReturnVal.speedSignal = PuckSignal::PuckSpeed::FAST;
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

	if(puckList.empty()) {
		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
		prioReturnVal.errorFlag = true;
		prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
		return prioReturnVal;
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

			it++;
		}

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
				delete *it;					// delete the puck from memory
				it = puckList.erase(it);	// delete the puck from list
				break;
			case PuckSignal::PuckReturn::SEND:
				acceptCounter++;
				prioReturnVal.puck = (*it);
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
			case PuckSignal::PuckReturn::SLIDE_FULL:
				acceptCounter++;

				sort.process(returnVal.puckReturn);

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
	}

	if(!prioReturnVal.errorFlag) {
		if(acceptCounter > 1 || acceptCounter < 0) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_ACCEPT;
			return prioReturnVal;
		}

		if(acceptCounter == 0) {
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

	if(puckList.empty()) {
		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
	}

	// everything OK
	return prioReturnVal;
}
