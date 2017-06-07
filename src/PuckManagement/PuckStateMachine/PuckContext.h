/*
 * PuckContext.h
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#ifndef PUCKCONTEXT_H_
#define PUCKCONTEXT_H_

#include "HeightSignal.h"

#include "PuckSignal.h"
#include <stdint.h>


#define machine (0) // 0 or 1

class PuckContext {
public:
	PuckContext(uint32_t puckID);
	PuckSignal::Return process(PuckSignal::Signal signal);

	// Getter for Puckmanager
	PuckSignal::PuckType getType() {
		return statePtr->puckType;
	}

	uint32_t getPuckID() {
		return statePtr->puckID;
	}




	/*******************************************
	 * SuperState
	 */
	struct PuckState {
		// Signals
		virtual void inletIn();
		virtual void inletOut();

		virtual void heightmeasurmentIn();
		virtual void heightmeasurmentOut();

		virtual void switchIn();
		virtual void switchOpen();

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

		uint32_t puckID;
		PuckSignal::PuckType puckType;

		// Timer stuff
		void startTimers();
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
	} transferState;

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
		void type();
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
		void switchOpen();
		void slideIn();
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
	 * Switch
	 */
	struct SwitchArea : public PuckState {
		void earlyTimer();
		void outletIn();
	};

	struct SwitchTimer : public PuckState {
		void outletIn();  //with guards
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
