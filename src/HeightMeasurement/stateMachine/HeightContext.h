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

#include <vector>
#include <functional>

class HeightContext {
private:
	// Forward declaration
	struct State *statePtr;
	struct Idle;
	struct Measuring;
	struct Normal;
	struct Surface;
	struct BitOrFlipped;
	struct Top;
	struct High;
	struct Low;
	struct Flipped;
	struct BitCoded;

	State state;
	vector<function<void(void)>> signalList = {
			[&] ( ) { statePtr->invalid(); },
			[&] ( ) { statePtr->timeout(); },
			[&] ( ) { statePtr->start(); },
			[&] ( ) { statePtr->wait(); },
			[&] ( ) { statePtr->resume(); },
			[&] ( ) { statePtr->holeHeight(); },
			[&] ( ) { statePtr->surfaceHeight(); },
			[&] ( ) { statePtr->refHeight(); },
			[&] ( ) { statePtr->patternRead(); },
			[&] ( ) { statePtr->lowHeight(); },
			[&] ( ) { statePtr->highHeight(); }
	};
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

	HeightContext();
	void process(Signal signal);
};

#endif /* HEIGHTCONTEXT_H_ */
/** @} */
