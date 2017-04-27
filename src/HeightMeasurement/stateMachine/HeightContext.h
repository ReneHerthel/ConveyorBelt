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

#ifndef HEIGHTCONTEXT_H_
#define HEIGHTCONTEXT_H_

#include <functional>
#include <vector>

#define MAX_BIT_SIZE 3
#define MIN_BIT_SIZE 3

class HeightContext {
private:

	/*
	 * @brief
	 */
	struct State {
		virtual void invalid();
		virtual void timeout();
		virtual void start();
		virtual void wait();
		virtual void resume();
		virtual void holeHeight();
		virtual void surfaceHeight();
		virtual void refHeight();
		virtual void patternRead();
		virtual void lowHeight();
		virtual void highHeight();

		virtual void entry();
	} *statePtr;

	/*
	 * @brief
	 */
	struct Idle : public State {
		void start();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Measuring : public State {
		void holeHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Normal : public State {
		void surfaceHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Surface : public State {
		void refHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct BitOrFlipped : public State {
		unsigned int index;
		bool pattern[MAX_BIT_SIZE];

		void patternRead();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Top : public BitOrFlipped {
		void refHeight();
		void lowHeight();
		void highHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct High : public BitOrFlipped {
		void surfaceHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Low : public BitOrFlipped {
		void surfaceHeight();
		void entry();
	};

	/*
	 * @brief
	 */
	struct Flipped : public BitOrFlipped {
		void entry();
	};

	/*
	 * @brief
	 */
	struct BitCoded : public BitOrFlipped {
		void entry();
	};

	/*
	 * @brief
	 */
	State state;

	/*
	 * @brief
	 */

	/*
	 * @brief
	 */
public:
	enum Signal {
		INVALID,
		TIMEOUT,

		START,
		WAIT,
		RESUME,

		HOLE_HEIGHT,
		SURFACE_HEIGHT,
		REF_HEIGHT,
		PATTERN_READ,

		LOW_HEIGHT,
		HIGH_HEIGHT
	};

	/*
	 * @brief
	 */
	HeightContext(int send_chid);

	/*
	 * @brief
	 * @param [signal]
	 */
	void process(Signal signal);

	int send_chid;
};

#endif /* HEIGHTCONTEXT_H_ */
/** @} */
