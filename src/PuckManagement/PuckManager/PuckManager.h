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

#include <list>

class PuckManager {
public:
	enum ActorSignal {
		START_MEASUREMENT,
		STOP_MEASUREMENT,
		OPEN_SWITCH,
		SEND_PUCK
	};

	enum ErrorSignal {
		PUCK_LOST,			// Late timer expired
		PUCK_MOVED,			// Puck triggered light barrier before early timer expired
		UNEXPECTED_SIGNAL,	// Signal could not be processed
		MULTIPLE_ACCEPT,	// Shouldn't happen - multiple pucks were triggered
		MULTIPLE_WARNING	// Shouldn't happen - multiple pucks were triggered
	};

	struct ManagerReturn {
		PuckSignal::PuckSpeed speedSignal;
		bool actorFlag;
		ActorSignal actorSignal;
		bool errorFlag;
		ErrorSignal errorSignal;
		bool slideFullFlag;
		PuckContext *puck;					// Null except on send Signal
	};

	PuckManager(int chid);
	~PuckManager();

	ManagerReturn process(PuckSignal::Signal signal);
	void addPuck(PuckContext *puck);

private:
	std::list<PuckContext*> puckList;
	uint16_t nextPuckID;
	int chid; /**< @brief ID for the pucks to give the timers*/
};

#endif /* PUCKMANAGER_H_ */
