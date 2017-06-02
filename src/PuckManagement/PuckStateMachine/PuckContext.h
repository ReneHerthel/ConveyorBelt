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

	Return process(); // todo: pass signal

private:

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

		virtual Return entry();

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
		void inletIn();
		void earlyTimer();
	};

	struct TransferWarning : PuckState {
		void earlyTimer();
	};

	struct TransferTimer : PuckState {
		void inletIn();
	};
	/*******************************************/

	/*******************************************
	 * Inlet
	 */
	struct Inlet : PuckState {
		void inletOut();
	};

	struct InletArea : PuckState {
		void earlyTimer();
		void heightmeasurmentIn();
	};

	struct InletWarning : PuckState {
		void earlyTimer();
	};

	struct InletTimer : PuckState {
		void heightmeasurementIn();
	};
	/*******************************************/

	/*******************************************
	 * Heightmeasurement
	 */
	struct Heightmeasurement : PuckState {
		void heightmeasurementOut();
		void type();
	};

	struct MeasurementType : PuckState {
		void heightMeasurementOut();
	};

	struct MeasurementArea : PuckState {
		void earlyTimer();
		void switchIn();
		void type();
	};

	struct MeasurementWarning : PuckState {
		void earlyTimer();
	};

	struct MeasurementTypeLate : PuckState {
		void earlyTimer();
		void switchIn();
	};

	struct MeasurementTimer : PuckState {
		void metalDetect();
		void switchIn();
	};
	/*******************************************/

	/*******************************************
	 * Type
	 */
	struct MetalType : PuckState {
		void switchIn();
	};

	struct TypeKnown : PuckState {
		void switchOpen();
		void slideIn();
	};
	/*******************************************/

	/*******************************************
	 * Slide
	 */
	struct SlideArea : PuckState {
		void slideOut();
		void lateTimer();
	};
	/*******************************************/

	/*******************************************
	 * Switch
	 */
	struct SwitchArea : PuckState {
		void earlyTimer();
		void outletIn();
	};

	struct SwitchWarning : PuckState {
		void earlyTimer();
	};

	struct SwitchTimer : PuckState {
		void outletIn();
	};
	/*******************************************/

	/*******************************************
	 * Outlet
	 */
	struct OutletArea : PuckState {
		void serialAccept();
	};

	struct InTransfer : PuckState {
		void serialReceived();
		void serialStop();
	};

	struct TransferStopped : PuckState {
		void serialResume();
	};

	struct Transferred : PuckState {
		void outletOut();
	};

	struct PhysicalTransfer : PuckState {

	};
	struct Taken : PuckState {

	};
	/*******************************************/
};

#endif /* PUCKCONTEXT_H_ */
