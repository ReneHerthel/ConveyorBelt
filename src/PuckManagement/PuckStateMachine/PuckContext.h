/*
 * PuckContext.h
 *
 *  Created on: 30.05.2017
 *      Author: abz908
 */

#ifndef PUCKCONTEXT_H_
#define PUCKCONTEXT_H_

class PuckContext {
public:

	enum PuckReturn {
		ACCEPT,
		DENY,
		ERROR,
		DELETE,
		SEND,
		EVALUATE,
		HEIGHT,
		SLIDE_FULL
	};

	PuckContext();

	PuckReturn process(); // todo: pass signal
	PuckReturn setType(signal_t type);

private:
	struct PuckState {
		virtual void inletIn();
		virtual void inletOut();

		virtual void heightmeasurmentIn();
		virtual void heightmeasurmentOut();

		virtual void switchIn();
		virtual void switchOut();

		virtual void slideIn();
		virtual void slideOut();

		virtual void outletIn();
		virtual void outletOut();

		virtual void metalDetect();

		virtual void serialReceived();

		virtual void earlyTimer();
		virtual void lateTimer();

		virtual PuckReturn entry();
	} *state;

	struct Error : PuckState {
		PuckReturn entry();
	};

	struct Inlet : PuckState {
		void inletIn();
		PuckReturn entry();
	};

	struct InletArea : PuckState {
		void earlyTimer();
		void heightmeasurmentIn();
		PuckReturn entry();
	};
};

#endif /* PUCKCONTEXT_H_ */
