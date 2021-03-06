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
#include "ISerializable.h"
#include <string.h>

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
		SLIDE_EMPTY,
		RECEIVED,
		WARNING
	};

	enum PuckSpeed {
		SLIDE_STOP, //Low prio for stopping in slide
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

	struct Data {
		HeightMeasurement::signal_t heightType;
		uint8_t metal;
		uint16_t height1;
		uint16_t height2;
	};

	// The serialized data
	struct PuckType : public ISerializable {
		PuckType(){};
        /*!  
         *  \brief Put input data into data member
         *  \argument [in] other Data to file
         *
         *  Allow assigning Data objects directly to data member
         */
		PuckType(Data data)
		: data(data)
		{};

		Data data;

		serialized serialize() override {
			serialized ser;
			ser.size = sizeof(data);
			ser.obj = new Data(data);
			return ser;
		}

		bool deserialize(void* ser) override {
			if(ser == nullptr) return false;
			data = *((Data*)ser);
			return true;
		}

		bool operator==(PuckType const &type) {
			return !memcmp(&data, &type.data, sizeof(data));
		}

	};
}

#endif
