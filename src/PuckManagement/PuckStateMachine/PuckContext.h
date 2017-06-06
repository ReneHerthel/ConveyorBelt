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

class PuckContext {
public:

	PuckContext();

	PuckSignal::Return process(); // todo: pass signal

private:

	void startTimers();

	/*******************************************
	 * SuperState
	 */
	struct PuckState {
		virtual PuckSignal::PuckSignal::Return inletIn();
		virtual PuckSignal::Return inletOut();

		virtual PuckSignal::Return heightmeasurmentIn();
		virtual PuckSignal::Return heightmeasurmentOut();

		virtual PuckSignal::Return switchIn();
		virtual PuckSignal::Return switchOpen();

		virtual PuckSignal::Return slideIn();
		virtual PuckSignal::Return slideOut();

		virtual PuckSignal::Return outletIn();
		virtual PuckSignal::Return outletOut();

		virtual PuckSignal::Return type();
		virtual PuckSignal::Return metalDetect();

		virtual PuckSignal::Return serialAccept();
		virtual PuckSignal::Return serialReceived();
		virtual PuckSignal::Return serialStop();
		virtual PuckSignal::Return serialResume();

		virtual PuckSignal::Return earlyTimer();
		virtual PuckSignal::Return lateTimer();

		virtual void entry();

		signal_t puckType;
		bool metal;
		uint32_t puckID;
		uint16_t highestHeight1;
		uint16_t highestHeight2;
		PuckSpeed aquiredSpeed;
	} *statePtr, state;


	/*******************************************/

	/*******************************************
	 * Transfer
	 */
	struct TransferArea : PuckState {
		PuckSignal::Return inletIn();
		PuckSignal::Return earlyTimer();
	};

	struct TransferTimer : PuckState {
		PuckSignal::Return inletIn();
	};
	/*******************************************/

	/*******************************************
	 * Inlet
	 */
	struct Inlet : PuckState {
		PuckSignal::Return inletOut();
	};

	struct InletArea : PuckState {
		PuckSignal::Return earlyTimer();
		PuckSignal::Return heightmeasurmentIn();
	};

	struct InletTimer : PuckState {
		PuckSignal::Return heightmeasurementIn();
	};
	/*******************************************/

	/*******************************************
	 * Heightmeasurement
	 */
	struct Heightmeasurement : PuckState {
		PuckSignal::Return heightmeasurementOut();
		PuckSignal::Return type();
	};


	struct MeasurementArea : PuckState {
		PuckSignal::Return earlyTimer();
		PuckSignal::Return switchIn();
		PuckSignal::Return type();
	};

	struct MeasurementTimer : PuckState {
		PuckSignal::Return switchIn();
	};

	struct MeasurementType : PuckState {
		PuckSignal::Return metalDetect();
		PuckSignal::Return switchIn();
	};
	/*******************************************/

	/*******************************************
	 * Type
	 */
	struct MetalType : PuckState {
		PuckSignal::Return switchIn();
	};

	struct TypeKnown : PuckState {
		PuckSignal::Return switchOpen();
		PuckSignal::Return slideIn();
	};
	/*******************************************/

	/*******************************************
	 * Slide
	 */
	struct SlideArea : PuckState {
		PuckSignal::Return slideOut();
		PuckSignal::Return lateTimer();
	};
	/*******************************************/

	/*******************************************
	 * Switch
	 */
	struct SwitchArea : PuckState {
		PuckSignal::Return earlyTimer();
		PuckSignal::Return outletIn();
	};

	struct SwitchTimer : PuckState {
		PuckSignal::Return outletIn();
	};
	/*******************************************/

	/*******************************************
	 * Outlet
	 */
	struct OutletArea : PuckState {
		PuckSignal::Return serialAccept();
	};

	struct InTransfer : PuckState {
		PuckSignal::Return outletOut();
		PuckSignal::Return serialStop();
	};

	struct TransferStopped : PuckState {
		PuckSignal::Return serialResume();
	};

	struct Transferred : PuckState {
		PuckSignal::Return serialReceived();
	};

	/*******************************************/
};

#endif /* PUCKCONTEXT_H_ */
