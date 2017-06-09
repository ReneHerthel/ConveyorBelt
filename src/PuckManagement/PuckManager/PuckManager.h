/*
 * PuckManager.h
 *
 *  Created on: 09.06.2017
 *      Author: aca592
 */

#ifndef PUCKMANAGER_H_
#define PUCKMANAGER_H_

#include "PuckSignal.h"
#include "PuckContext.h"

class PuckManager {
public:
	enum ActorSignal {
		START_MEASUREMENT,
		OPEN_SWITCH,
		SEND_PUCK
	};

	enum ErrorSignal {
		PUCK_LOST,
		PUCK_MOVED,
		UNEXPECTED_SIGNAL
	};

	struct ManagerReturn {
		PuckSignal::PuckSpeed speedSignal;
		uint8_t actorFlag;
		ActorSignal actorSignal;
		uint8_t errorFlag;
		ErrorSignal errorSignal;
	};

	PuckManager();
	~PuckManager();

	ManagerReturn process(PuckSignal::Signal signal);
	void addPuck(PuckContext *puck);

private:
	std::vector<PuckContext*> puckList;
	uint16_t nextPuckID;
};

#endif /* PUCKMANAGER_H_ */
