/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    height_context
  * @{
  *
  * @brief      Statemachine for the height measurement.
  *
  * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#include "HeightContext.h"
#include <sys/siginfo.h>
#include <sys/neutrino.h>

#define MAX_BIT_SIZE 3
#define MIN_BIT_SIZE 3

class HeightContext {

private:

	/*
	 * @brief
	 */
	struct State {
		State() {
			new (this) Idle;
		}

		virtual void invalid() {
			// todo MsgSendPulse_r(invalid)
			new (this) State;
		}

		virtual void timeout() {
			// todo MsgSendPulse_r(timeout)
			new (this) State;
		}


		virtual void start() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}

		virtual void wait() {
			// todo stoptimer()
		}

		virtual void resume() {
			// todo resumeTimer()
		}

		virtual void holeHeight() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}

		virtual void surfaceHeight() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}

		virtual void refHeight() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}

		virtual void patternRead() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}


		virtual void lowHeight() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}

		virtual void highHeight() {
			// todo MsgSendPulse_r(unexpected)
			new (this) State;
		}
	} *statePtr;

	/*
	 * @brief
	 */
	struct Idle : public State {
		Idle() {
			// todo stopMeasuring()
			// todo stopTimer()
		}

		void start() {
			new (this) Measuring;
		}
	};

	/*
	 * @brief
	 */
	struct Measuring : public State {
		Measuring() {
			// todo startMeasuring()
			// todo startTimer()
		}

		void holeHeight() {
			new (this) Normal;
		}
	};

	/*
	 * @brief
	 */
	struct Normal : public State {
		void surfaceHeight() {
			new (this) Surface;
		}
	};

	/*
	 * @brief
	 */
	struct Surface : public State {
		void refHeight() {
			new (this) Idle;
		}
	};

	/*
	 * @brief
	 */
	struct BitOrFlipped : public State {
		unsigned int index;
		bool pattern[MAX_BIT_SIZE];

		BitOrFlipped() {
			index = 0;
			pattern = {0, 0, 0};
			new (this) Top;
		}

		void patternRead() {
			new (this) Idle;
		}
	};

	/*
	 * @brief
	 */
	struct Top : public BitOrFlipped {
		Top() {
			if (index > MAX_BIT_SIZE || index < MIN_BIT_SIZE) {
				invalid();
			}
		}

		void refHeight() {
			if (index == 0) {
				new (this) Flipped;
			}
			else {
				new (this) BitCoded;
			}
		}

		void lowHeight() {
			new (this) Low;
		}

		void highHeight() {
			new (this) High;
		}
	};

	/*
	 * @brief
	 */
	struct High : public BitOrFlipped {
		High () {
			pattern[index] = 1;
			index++;
		}

		void surfaceHeight() {
			new (this) Top;
		}
	};

	/*
	 * @brief
	 */
	struct Low : public BitOrFlipped {
		Low() {
			pattern[index] = 0;
			index++;
		}

		void surfaceHeight() {
			new (this) Top;
		}
	};

	/*
	 * @brief
	 */
	struct Flipped : public BitOrFlipped {
		Flipped() {
			//todo msgSend(flipped)
			patternRead();
		}
	};

	/*
	 * @brief
	 */
	struct BitCoded : public BitOrFlipped {
		BitCoded() {
			//todo msgSend(pattern)
			patternRead();
		}
	};

public:
	HeightContext::HeightContext()
	: statePtr(&state)
	{
		// Nothing todo so far.
	}

	void HeightContext::process(Signal signal) {
		(signalList[signal]);
	}
};
/** @} */
