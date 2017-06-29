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
#include "PuckSortContext.h"

#include <list>

class PuckManager {
public:
	enum ActorSignal : int32_t{
		START_MEASUREMENT,
		STOP_MEASUREMENT,
		OPEN_SWITCH,
		SEND_PUCK,
		RECEIVED_PUCK,
		ACCEPTED_PUCK,
		SEND_SLIDE_FULL,
		SEND_SLIDE_EMPTY,
		SEND_RESUME
	};

	enum ErrorSignal : int32_t{
		PUCK_LOST,			// Late timer expired
		PUCK_MOVED,			// Puck triggered light barrier before early timer expired
		UNEXPECTED_SIGNAL,	// Signal could not be processed
		NOT_ACCEPTED,		// Signal was not accepted by the pucks
		MULTIPLE_ACCEPT,	// Shouldn't happen - multiple pucks were triggered
		MULTIPLE_WARNING,	// Shouldn't happen - multiple pucks were triggered
		BOTH_SLIDES_FULL /*!< All slides are full*/
	};

	struct ManagerReturn {
		PuckSignal::PuckSpeed speedSignal;
		bool actorFlag;
		ActorSignal actorSignal;
		bool errorFlag;
		ErrorSignal errorSignal;
		PuckSignal::PuckType *puckType;					// Null except on send Signal
	};


	PuckManager(int chid);
	~PuckManager();
	/*!
     *  \brief Reset all
     */
	void reset();
	/*!
     *  \brief Reset the puck list
     */
	void resetPucks();
	/*!
     *  \brief Reset the slide conditionals
     */
    void resetSlides(void);

	ManagerReturn process(PuckSignal::Signal signal);

	ManagerReturn newPuck(PuckSignal::PuckType type);

private:
	void addPuck(PuckContext *puck);
	PuckSignal::PuckSpeed getCurrentSpeed(void);
	void handlePuckTimer(const PuckSignal::Signal& signal, ManagerReturn& prioReturnVal);
	void handlePuckSignal(const PuckSignal::Signal& signal, int32_t &acceptCounter, int32_t &warningCounter, ManagerReturn& prioReturnVal);
	bool passToPuckSort(const PuckSignal::Signal& signal, ManagerReturn& prioReturnVal);
	bool checkErrorMetal(const PuckSignal::Signal& signal);
	bool checkSerialError(const PuckSignal::Signal& signal);
    /*!
     *  \brief Check if all slides are full and set error signal accordingly
     *  \argument [in] prioReturnVal to set error in
     */
	void setErrorOnBothSlidesAreFull(ManagerReturn &prioReturnVal);

	std::list<PuckContext*> puckList;
	uint16_t nextPuckID;
	int chid; /**< @brief ID for the pucks to give the timers*/

	PuckSortContext sort;
};

#endif /* PUCKMANAGER_H_ */
