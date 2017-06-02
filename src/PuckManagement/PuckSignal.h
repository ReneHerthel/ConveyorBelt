/*
 * PuckSignal.h
 *
 *  Created on: 02.06.2017
 *      Author: abz908
 */

#ifndef PUCKSIGNAL_H_
#define PUCKSIGNAL_H_

namespace PuckSignal {

	enum PuckReturn {
		ACCEPT,
		DENY,
		ERROR,
		DELETE,
		SEND,
		EVALUATE,
		HEIGHT,
		SLIDE_FULL,
		WARNING
	};

	enum PuckSpeed {
		FAST,
		SLOW,
		STOPPED
	};

	struct Return {
		PuckReturn puckReturn;
		PuckSpeed puckSpeed;
	};

	struct Signal {
		// todo: merge signals for this type
	};

}

#endif
