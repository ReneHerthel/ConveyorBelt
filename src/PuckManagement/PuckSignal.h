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
#include "Signals.h"

#include <stdint.h>

namespace PuckSignal {

	enum PuckReturn {
		ACCEPT,
		DENY,
		ERROR,
		DELETE,
		SEND,
		EVALUATE,
		START_HEIGHT,
		STOP_HEIGHT,
		SLIDE_FULL,
		RECEIVED,
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

	union TimerSignal {
		struct TIMER_INFO {
			uint16_t puckID;
			TimerType type;
		} TimerInfo __attribute__((packed));
		int32_t value;
	};

	enum SignalType {
		HEIGHT_SIGNAL,
		TIMER_SIGNAL,
		INTERRUPT_SIGNAL,
		SERIAL_SIGNAL
	};

	struct Signal {
		SignalType signalType;
		HeightMeasurement::signal_t heightSignal;
		TimerSignal timerSignal;
		interrupts::interruptSignals interruptSignal;
		Serial_n::ser_proto_msg serialSignal;
	};

	struct PuckType {
		HeightMeasurement::signal_t heightType;
		uint8_t metal;
		uint16_t height1;
		uint16_t height2;
	};
}

#endif
