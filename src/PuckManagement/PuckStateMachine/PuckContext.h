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


#define machine (0) // 0 or 1

class PuckContext {
public:

	PuckContext();
	void process(); // todo: pass signal

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

		PuckSignal::Return returnValue;

		signal_t puckType;
		bool metal;
		uint32_t puckID;
		uint16_t highestHeight1;
		uint16_t highestHeight2;
		PuckSignal::PuckSpeed aquiredSpeed;
	} *statePtr, state;


	/*******************************************/

#if machine
	/*******************************************
	 * Transfer
	 */
	struct TransferArea : PuckState {
		void inletIn();
		void earlyTimer();
	};

	struct TransferTimer : PuckState {
		void inletIn();
	};
	/*******************************************/
#endif

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


	struct MeasurementArea : PuckState {
		void earlyTimer();
		void switchIn();
		void type();
	};

	struct MeasurementTimer : PuckState {
		void switchIn();
		void metaldetect();
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

	struct SwitchTimer : PuckState {
		void outletIn();  //with guards
	};
	/*******************************************/

	/*******************************************
	 * Outlet
	 */
	struct OutletArea : PuckState {
#if !machine
		void serialAccept();
#else
		void outletOut();
#endif
	};

#if !machine
	struct InTransfer : PuckState {
		void outletOut();
		void serialStop();
	};

	struct TransferStopped : PuckState {
		void serialResume();
	};

	struct Transferred : PuckState {
		void serialReceived();
	};
#endif
	/*******************************************/
};

#endif /* PUCKCONTEXT_H_ */
