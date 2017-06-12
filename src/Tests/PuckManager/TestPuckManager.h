/*
 * TestPuckManager.h
 *
 *  Created on: 12.06.2017
 *      Author: aca592
 */

#ifndef TESTPUCKMANAGER_H_
#define TESTPUCKMANAGER_H_

#include "TestCase.h"
#include "TestFramework.h"

#include "PuckContext.h"
#include "PuckSignal.h"
#include "PuckManager.h"
#include "Signals.h"
#include "HeightSignal.h"
#include "SerialProtocoll.h"

class TestPuckManager : public TestCase {
public:
	TestPuckManager(int id, std::string brief) : TestCase(id, brief) { };
protected:
	TEST(test1);
	TEST_CASE_METHODS;
private:
	PuckManager *manager;

#if !machine
	PuckSignal::Signal signalArrayLongestPath[17] {
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::METAL_DETECT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::SWITCH_OPEN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::TIMER_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::OUTLET_IN, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::STOP_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::RESUME_SER},
			{PuckSignal::SignalType::INTERRUPT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::OUTLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
			{PuckSignal::SignalType::SERIAL_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::RECEIVED_SER}
	};

	PuckManager::ManagerReturn returnArrayLongestPath[17] {
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::SLOW, true, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, true, PuckManager::ActorSignal::OPEN_SWITCH, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, true, PuckManager::ActorSignal::SEND_PUCK, false, PuckManager::ErrorSignal::PUCK_LOST, false, (PuckContext*)0x123456},
			{PuckSignal::PuckSpeed::SLOW, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::STOP, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::SLOW, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::SLOW, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr},
			{PuckSignal::PuckSpeed::FAST, false, PuckManager::ActorSignal::START_MEASUREMENT, false, PuckManager::ErrorSignal::PUCK_LOST, false, nullptr}
	};
#else
	PuckSignal::Signal signalArrayLongestPath[19] {
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
			{PuckSignal::SignalType::HEIGHT_SIGNAL, {0}, {0, PuckSignal::TimerType::EARLY_TIMER}, interrupts::interruptSignals::INLET_OUT, Serial_n::ser_proto_msg::ACCEPT_SER},
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
#endif
};

#endif /* TESTPUCKMANAGER_H_ */