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
	resetPucks();
}

void PuckManager::reset() {
	resetPucks();
	resetSlides();
}

void PuckManager::resetPucks() {
	std::list<PuckContext*>::iterator it = puckList.begin();
	while(it != puckList.end()) {
		LOG_DEBUG <<"[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
		delete *it;					// delete the puck from memory
		it = puckList.erase(it);	// delete the puck from list
	}
}

void PuckManager::resetSlides(void) {
	sort.resetSlides();
}

PuckManager::ManagerReturn PuckManager::newPuck(PuckSignal::PuckType type) {
	LOG_SCOPE;
	ManagerReturn ret;
	ret.errorFlag = false;
	ret.actorFlag = true;
	ret.speedSignal = PuckSignal::PuckSpeed::SLOW;
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

PuckSignal::PuckSpeed PuckManager::getCurrentSpeed() {
	PuckSignal::PuckSpeed speed = PuckSignal::PuckSpeed::SLIDE_STOP;
	std::list<PuckContext*>::iterator it = puckList.begin();
	while (it != puckList.end()) {
		if ((*it)->getCurrentSpeed() > speed) {
			// Check for speed prio
			speed = (*it)->getCurrentSpeed();
		}
		it++;
	}

	if(puckList.empty()) {
		speed = PuckSignal::PuckSpeed::STOP;
	}
	return speed;
}

void PuckManager::handlePuckTimer(const PuckSignal::Signal& signal, ManagerReturn& prioReturnVal) {
	LOG_DEBUG << "[PuckManager] Handle Puck Timer \n";
	std::list<PuckContext*>::iterator it = puckList.begin();
	while (it != puckList.end()) {
		// check for puckID
		uint16_t currentPuckID = (*it)->getPuckID();
		if (currentPuckID == signal.timerSignal.TimerInfo.puckID) {
			// pass the timer signal
			PuckSignal::Return returnVal = (*it)->process(signal);
			// check return value
			if (returnVal.puckReturn == PuckSignal::PuckReturn::SLIDE_FULL) {
				LOG_DEBUG << "[PuckManager] Puck returned Slide full \n";
				sort.process(returnVal.puckReturn);
				setErrorOnBothSlidesAreFull(prioReturnVal);
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::SEND_SLIDE_FULL;
			} else if (returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT
					&& returnVal.puckReturn != PuckSignal::PuckReturn::ERROR) {
				// puck should be triggered on accept or error -> unexpected otherwise
				prioReturnVal.errorFlag = true;
				prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
			} else if (returnVal.puckReturn == PuckSignal::PuckReturn::ERROR) {
				prioReturnVal.errorFlag = true;
				prioReturnVal.errorSignal = ErrorSignal::PUCK_LOST; //Late Timer expiered
			}
		}
		it++;
	}
}

void PuckManager::handlePuckSignal(const PuckSignal::Signal &signal, int32_t &acceptCounter, int32_t &warningCounter, ManagerReturn &prioReturnVal) {
	LOG_DEBUG << "[PuckManager] Handle Puck Signal \n";
	// check the signal for every puck in the list
	if(puckList.empty()) {
		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
		prioReturnVal.errorFlag = true;
		prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
	}

	std::list<PuckContext*>::iterator it = puckList.begin();
	while (it != puckList.end()) {
		PuckSignal::Return returnVal = (*it)->process(signal);

		switch (returnVal.puckReturn) {
		case PuckSignal::PuckReturn::ACCEPT:
			acceptCounter++;
			break;
		case PuckSignal::PuckReturn::DELETE:
			prioReturnVal.actorFlag = true;
			prioReturnVal.actorSignal = ActorSignal::SEND_RESUME;
			acceptCounter++;
			LOG_DEBUG << "[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
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
			if (!sort.process((*it)->getType())) {
				prioReturnVal.actorFlag = true;
				prioReturnVal.actorSignal = ActorSignal::OPEN_SWITCH;
			}
			setErrorOnBothSlidesAreFull(prioReturnVal);
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
			setErrorOnBothSlidesAreFull(prioReturnVal);
			prioReturnVal.actorFlag = true;
			prioReturnVal.actorSignal = ActorSignal::SEND_SLIDE_EMPTY;
			LOG_DEBUG << "[Puck" + std::to_string((*it)->getPuckID()) + "] was deleted \n";
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
			//return prioReturnVal;
		}

		if (returnVal.puckReturn != PuckSignal::PuckReturn::DELETE || returnVal.puckReturn != PuckSignal::PuckReturn::SLIDE_EMPTY) { //if a puck was deleted, you should not increment the iteratpr
			++it;
		}
	}

	prioReturnVal.speedSignal = getCurrentSpeed();

	/* No one Accepted the signal, so it is likely to be unexpected*/
	if(acceptCounter == 0) {
		prioReturnVal.errorFlag = true;
		prioReturnVal.errorSignal = ErrorSignal::NOT_ACCEPTED;
	}
}

bool PuckManager::passToPuckSort(const PuckSignal::Signal& signal, ManagerReturn& prioReturnVal) {
	LOG_DEBUG << "[PuckManager] Pass to Pucksort \n";
	if ( signal.signalType == PuckSignal::SignalType::SERIAL_SIGNAL
		 && (signal.serialSignal == Serial_n::ser_proto_msg::SLIDE_FULL_SER
		 || signal.serialSignal == Serial_n::ser_proto_msg::SLIDE_EMTPY_SER)){
		sort.process(signal.serialSignal);
		setErrorOnBothSlidesAreFull(prioReturnVal);
		LOG_DEBUG << "[PuckManager] Returning with with Slide management only \n";
		return true;
	} else {
		return false;
	}
}

bool PuckManager::checkErrorMetal(const PuckSignal::Signal& signal) {
	// metal detect hot fix
	return (signal.signalType == PuckSignal::SignalType::INTERRUPT_SIGNAL
			&& signal.interruptSignal
			== interrupts::interruptSignals::METAL_DETECT);
}

void PuckManager::setErrorOnBothSlidesAreFull(ManagerReturn &prioReturnVal) {
	if (sort.areBothSlidesFull()) {
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::BOTH_SLIDES_FULL;
	}
}

bool PuckManager::checkSerialError(const PuckSignal::Signal& signal) {
	/* Accept serial RESUME and STOP signals */
	return (signal.signalType == PuckSignal::SignalType::SERIAL_SIGNAL
			&& (signal.serialSignal == Serial_n::ser_proto_msg::STOP_SER
			|| signal.serialSignal == Serial_n::ser_proto_msg::RESUME_SER));
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

	if(passToPuckSort(signal, prioReturnVal)){ //Only pucksort is intrested in signal
			prioReturnVal.speedSignal = getCurrentSpeed(); //Always set speed
			LOG_DEBUG << "[PuckManager] Returning with pass to puck sort only \n";
			return prioReturnVal;
	}

	prioReturnVal.speedSignal = getCurrentSpeed(); //Always set speed


#if !machine // machine0
	// check for first interrupt signal - puck must be created
	if(	signal.signalType == PuckSignal::SignalType::INTERRUPT_SIGNAL &&
		signal.interruptSignal == interrupts::interruptSignals::INLET_IN) {

		addPuck(new PuckContext(chid));
		prioReturnVal.speedSignal = getCurrentSpeed(); //Always set speed


		return prioReturnVal;
	}

	// signal can be passed for speed prio -> every puck should return deny
#endif

	// Pass the timer signal to the given puckID
	if(signal.signalType == PuckSignal::SignalType::TIMER_SIGNAL) {
		handlePuckTimer(signal, prioReturnVal);
		prioReturnVal.speedSignal = getCurrentSpeed(); //Always set speed
		LOG_DEBUG << "[PuckManager] Returning with with timer management only \n";
		return prioReturnVal;
	} else {
		// check the signal for every puck in the list
		handlePuckSignal(signal, acceptCounter, warningCounter, prioReturnVal);
	}

	/* Signal was unexpected for the pucks, might be expected somewhere else */
	if(prioReturnVal.errorFlag && prioReturnVal.errorSignal == ErrorSignal::NOT_ACCEPTED){
		if(checkErrorMetal(signal)){
			LOG_DEBUG << "[PuckManager] Error was from Metall \n";
			prioReturnVal.errorFlag = false;
		} else if(checkSerialError(signal)){
			LOG_DEBUG << "[PuckManager] Error was from Serial \n";
			prioReturnVal.errorFlag = false;
		} else {
			LOG_DEBUG << "[PuckManager] Transform NOT_ACCEPTED to UNEXPECTED_SIGNAL \n";
			prioReturnVal.errorSignal = ErrorSignal::UNEXPECTED_SIGNAL;
		}
	}

	/*if(!prioReturnVal.errorFlag) {
		if(acceptCounter > 1 || acceptCounter < 0) {
			LOG_DEBUG << "[PuckManager] Returning with MULTIPLE_ACCEPT";
			prioReturnVal.errorFlag = true;
			prioReturnVal.errorSignal = ErrorSignal::MULTIPLE_ACCEPT;
			return prioReturnVal;
		}
	}*/

	setErrorOnBothSlidesAreFull(prioReturnVal);

	if(puckList.empty()) {
		prioReturnVal.speedSignal = PuckSignal::PuckSpeed::STOP;
	}

	prioReturnVal.speedSignal = getCurrentSpeed(); //Always set speed

	LOG_DEBUG << "Puck Manager returns: Speed " << prioReturnVal.speedSignal << " Actor Flag " << prioReturnVal.actorFlag
			 << " Actor Signal " << prioReturnVal.actorSignal << " Error Flag " << prioReturnVal.errorFlag
			 << " Error Signal " << prioReturnVal.errorSignal << " \n";

	// everything OK
	return prioReturnVal;
}
