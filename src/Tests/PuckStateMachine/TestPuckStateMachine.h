/*
 * TestPuckStateMachine.h
 *
 *  Created on: 08.06.2017
 *      Author: aca592
 */

#ifndef TESTPUCKSTATEMACHINE_H_
#define TESTPUCKSTATEMACHINE_H_

#include "TestCase.h"
#include "TestFramework.h"

#include "PuckContext.h"
#include "PuckSignal.h"
#include "Signals.h"
#include "HeightSignal.h"
#include "SerialProtocoll.h"
#include "Calibration.h"
#include "PulseMessageReceiverService.h"



class TestPuckStateMachine : public TestCase {
public:
	TestPuckStateMachine(int id, std::string brief) : TestCase(id, brief) { };
protected:
	TEST(test1);
	TEST(test2);
	TEST(test3);
	TEST_CASE_METHODS;

	rcv::PulseMessageReceiverService timerReceiver;
	int chid;
private:
	PuckContext *context;
	PuckSignal::TimerSignal earlyTimer = {
			.TimerInfo = {
				.puckID = 0,
				.type = PuckSignal::TimerType::EARLY_TIMER
			}
	};

	PuckSignal::TimerSignal lateTimer = {
			.TimerInfo = {
				.puckID = 0,
				.type = PuckSignal::TimerType::LATE_TIMER
			}
	};

#if !machine
	PuckSignal::Signal signalArrayLongestPath[19] {
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::METAL_DETECT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SWITCH_OPEN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::OUTLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::OUTLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::STOP_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::RESUME_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::OUTLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::RECEIVED_SER}
	};

	PuckSignal::Return returnArrayLongestPath[19] {
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::START_HEIGHT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::STOP_HEIGHT, PuckSignal::PuckSpeed::FAST},	// changed from accept -> need to test
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::EVALUATE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::SEND, PuckSignal::PuckSpeed::STOP},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::STOP},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::DELETE, PuckSignal::PuckSpeed::FAST},
	};

	PuckSignal::Signal signalArraySlidePath[12] {
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SLIDE_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			//Special last
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, earlyTimer, interrupts::interruptSignals::SLIDE_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, lateTimer, interrupts::interruptSignals::SLIDE_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
	};

	PuckSignal::Return returnArraySlidePath[12] {
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::START_HEIGHT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::STOP_HEIGHT, PuckSignal::PuckSpeed::FAST},	// changed from accept -> need to test
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::EVALUATE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			//Special last
			{PuckSignal::PuckReturn::DELETE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::SLIDE_FULL, PuckSignal::PuckSpeed::FAST},
	};
#else
	PuckSignal::Signal signalArrayLongestPath[18] {
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			//
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::METAL_DETECT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_OPEN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::OUTLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::OUTLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			//
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::OUTLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
	};

	PuckSignal::Return returnArrayLongestPath[18] {
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			//
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::START_HEIGHT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::STOP_HEIGHT, PuckSignal::PuckSpeed::FAST},	// changed from accept -> need to test
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::EVALUATE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::STOP},
			{PuckSignal::PuckReturn::DELETE, PuckSignal::PuckSpeed::FAST},
	};

	PuckSignal::Signal signalArraySlidePath[15] {
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			//
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SLIDE_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			//Special last
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SLIDE_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::LATE_TIMER}, interrupts::interruptSignals::SLIDE_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
	};

	PuckSignal::Return returnArraySlidePath[15] {
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			//
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::START_HEIGHT, PuckSignal::PuckSpeed::SLOW},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::STOP_HEIGHT, PuckSignal::PuckSpeed::FAST},	// changed from accept -> need to test
			{PuckSignal::PuckReturn::WARNING, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::EVALUATE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::ACCEPT, PuckSignal::PuckSpeed::FAST},
			//Special last
			{PuckSignal::PuckReturn::DELETE, PuckSignal::PuckSpeed::FAST},
			{PuckSignal::PuckReturn::SLIDE_FULL, PuckSignal::PuckSpeed::FAST},
	};
#endif
};

#endif /* TESTPUCKSTATEMACHINE_H_ */
