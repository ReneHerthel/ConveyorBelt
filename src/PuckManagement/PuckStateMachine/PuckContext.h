/*
 * PuckContext.h
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#ifndef PUCKCONTEXT_H_
#define PUCKCONTEXT_H_

#include "HeightSignal.h"

class PuckContext {
public:

	PuckContext();

	PuckReturn process(); // todo: pass signal
	PuckReturn setType(signal_t type);

private:
	signal_t puckType;
	bool metal;
	uint32_t puckID;

	void startTimers();

	/*******************************************
	 * SuperState
	 */
	struct PuckState {
		virtual void inletIn();
		virtual void inletOut();

		virtual void heightmeasurmentIn();
		virtual void heightmeasurmentOut();

		virtual void switchIn();
		virtual void switchOut();
		virtual void switchOpen();

		virtual void slideIn();
		virtual void slideOut();

		virtual void outletIn();
		virtual void outletOut();

		virtual void metalDetect();

		virtual void serialReceived();

		virtual void earlyTimer();
		virtual void lateTimer();

		virtual PuckReturn entry();

		PuckReturn returnVal;
		PuckContext *context;
	} *statePtr, state;


	/*******************************************/

	/*******************************************
	 * Transfer
	 */
	struct TransferArea : PuckState {
		void inletIn();
		void earlyTimer();
		PuckReturn entry();
	};

	struct TransferWarning : PuckState {
		void earlyTimer();
		PuckReturn entry();
	};

	struct TransferTimer : PuckState {
		void inletIn();
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Inlet
	 */
	struct Inlet : PuckState {
		void inletOut();
		PuckReturn entry();
	};

	struct InletArea : PuckState {
		void earlyTimer();
		void heightmeasurmentIn();
		PuckReturn entry();
	};

	struct InletWarning : PuckState {
		void earlyTimer();
		PuckReturn entry();
	};

	struct InletTimer : PuckState {
		void heightmeasurementIn();
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Heightmeasurement
	 */
	struct Heightmeasurement : PuckState {
		void heightmeasurementOut();
		PuckReturn entry();
	};

	struct MeasurementArea : PuckState {
		void earlyTimer();
		void switchIn();
		PuckReturn entry();
	};

	struct MeasurementWarning : PuckState {
		void earlyTimer();
		PuckReturn entry();
	};

	struct MeasurementTimer : PuckState {
		void metalDetect();
		void switchIn();
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Type
	 */
	struct MetalType : PuckState {
		void switchIn();
		PuckReturn entry();
	};

	struct TypeKnown : PuckState {
		void switchOpen();
		void slideIn();
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Slide
	 */
	struct SlideArea : PuckState {
		void slideOut();
		void lateTimer();
		PuckReturn entry();
	};

	struct SlideFull : PuckState {
		PuckReturn entry(); 			//e-Transition
	};

	struct InSlide : PuckState {
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Switch
	 */
	struct SwitchArea : PuckState {
		void earlyTimer();
		void outletIn();
		PuckReturn entry();
	};

	struct SwitchWarning : PuckState {
		void earlyTimer();
		PuckReturn entry();
	};

	struct SwitchTimer : PuckState {
		void outletIn();
		PuckReturn entry();
	};
	/*******************************************/

	/*******************************************
	 * Outlet
	 */
	struct OutletArea : PuckState {
		void outletOut();
		PuckReturn entry();
	};

	struct InTransfer : PuckState {
		void serialReceived();
		PuckReturn entry();
	};

	struct Transferred : PuckState {
		PuckReturn entry();
	};
	/*******************************************/
};

#endif /* PUCKCONTEXT_H_ */
