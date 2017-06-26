/*
 * PuckContext.h
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#ifndef PUCKCONTEXT_H_
#define PUCKCONTEXT_H_

#include "HeightSignal.h"
#include "Signals.h"
#include "PuckSignal.h"
#include <stdint.h>
#include "SerialProtocoll.h"
#include "DistanceTracker.h"
#include "DistanceEnum.h"
#include "ISerializable.h"

#ifdef VARIANT_Belt0
#define machine (0) // 0 or 1
#else
#define machine (1) // 0 or 1
#endif

#define ONE_MACHINE_TESTING 0
#define TIMERCODE 25 //TODO fill with right PulseCode
#define SHORT_DELTA 0.9
#define QUICK_SHORT_DELTA 0.4

#define WIDE_DELTA 1.25
#define VERY_WIDE_DELTA 3.0
class PuckContext {
private:

	DistanceTracker shortDistance;
	DistanceTracker wideDistance;



public:
	PuckContext(int chid);
	PuckContext(int chid, PuckSignal::PuckType puckType, uint16_t puckId);

	PuckSignal::Return process(PuckSignal::Signal signal);

	// Getter for Puckmanager
	PuckSignal::PuckType getType() {
		return statePtr->puckType;
	}

	uint16_t getPuckID() {
		return statePtr->puckID;
	}

	void setPuckID(uint16_t puckID) {
		statePtr->puckID = puckID;
	}

	PuckSignal::PuckSpeed getCurrentSpeed() {
		return statePtr->returnValue.puckSpeed;
	}


	/*******************************************
	 * SuperState
	 */
	struct PuckState {
		// Signals
		virtual void inletIn();
		virtual void inletOut();

		virtual void heightmeasurementIn();
		virtual void heightmeasurementOut();

		virtual void switchIn();
		virtual void switchOut();

		virtual void slideIn();
		virtual void slideOut();

		virtual void outletIn();
		virtual void outletOut();

		virtual void type();
		virtual void metalDetect();

		virtual void serialAccept();
		virtual void serialReceived();
		virtual void serialStop();
		virtual void serialResume();

		virtual void earlyTimer();
		virtual void lateTimer();

		// The return struct for the PuckManager
		PuckSignal::Return returnValue;

		uint16_t puckID;
		PuckSignal::PuckType puckType;

		// Timer stuff

		DistanceTracker *shortDistance;
		DistanceTracker *wideDistance;

		void startTimers(DistanceSpeed::lb_distance distance);
		void startTimersWithDelta(DistanceSpeed::lb_distance distance,double earlyDelta,double lateDelta);
		void stopTimer();
	} *statePtr;
	/*******************************************/

#if machine
	/*******************************************
	 * Transfer
	 */
	struct TransferArea : public PuckState {
		void inletIn();
		void earlyTimer();
		void serialStop();
	} transferState;

	struct TransferStoppedInlet : public PuckState {
		void serialResume();
	};


	struct TransferTimer : public PuckState {
		void inletIn();
	};
	/*******************************************/
#endif

	/*******************************************
	 * Inlet
	 */
	struct Inlet : public PuckState {
		void inletOut();
	} inletState;

	struct InletArea : public PuckState {
		void earlyTimer();
		void heightmeasurementIn();
	};

	struct InletTimer : public PuckState {
		void heightmeasurementIn();
	};
	/*******************************************/

	/*******************************************
	 * Heightmeasurement
	 */
	struct Heightmeasurement : public PuckState {
		void heightmeasurementOut();
		void type();
	};


	struct MeasurementArea : public PuckState {
		void earlyTimer();
		void switchIn();
		//void type(); 	-- makes problems
	};

	struct MeasurementTimer : public PuckState {
		void switchIn();
		void metalDetect();
	};
	/*******************************************/

	/*******************************************
	 * Type
	 */
	struct MetalType : public PuckState {
		void switchIn();
	};

	struct TypeKnown : public PuckState {
		void switchOut();

	};
	/*******************************************/

	/*******************************************
	 * Switch
	 */
	struct SwitchArea : public PuckState {
		void earlyTimer();
		void outletIn();
		void slideIn();
	};

	struct SwitchTimer : public PuckState {
		void outletIn();  //with guards
	};
	/*******************************************/

	/*******************************************
	 * Slide
	 */
	struct SlideArea : public PuckState {
		void slideOut();
		void lateTimer();
	};
	/*******************************************/

	/*******************************************
	 * Outlet
	 */
	struct OutletArea : public PuckState {
#if !machine
		void serialAccept();
#else
		void outletOut();
#endif
	};

#if !machine
	struct InTransfer : public PuckState {
		void outletOut();
		void serialStop();
	};

	struct TransferStopped : public PuckState {
		void serialResume();
	};

	struct Transferred : public PuckState {
		void serialReceived();
	};
#endif
	/*******************************************/
};

#endif /* PUCKCONTEXT_H_ */
