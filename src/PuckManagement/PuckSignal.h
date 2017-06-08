/*
 * PuckSignal.h
 *
 *  Created on: 02.06.2017
 *      Author: abz908
 */

#ifndef PUCKSIGNAL_H_
#define PUCKSIGNAL_H_

#include "HeightSignal.h"
#include "SerialProtocoll.h"

#include <stdint.h>

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
		STOP
	};

	struct Return {
		PuckReturn puckReturn;
		PuckSpeed puckSpeed;
	};

	enum TimerType : uint8_t {
		EARLY_TIMER,
		LATE_TIMER
	};

	struct TimerSignal {
		uint16_t puckID;
		TimerType type;
	} __attribute__((packed));

	enum SignalType {
		HEIGHT_SIGNAL,
		TIMER_SIGNAL,
		INTERRUPT_SIGNAL,
		SERIAL_SIGNAL
	};

	struct Signal {
		SignalType signalType;
		signal_t heightSignal;
		TimerSignal timerSignal;
		interrupts::InterruptSignals interruptSignal;
		msg serialSignal;
	};

	struct PuckType {
		signal_t heightType;
		uint8_t metal;
		uint16_t height1;
		uint16_t height2;
	};
}

#endif
