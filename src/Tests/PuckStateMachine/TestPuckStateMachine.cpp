/*
 * TestPuckStateMachine.cpp
 *
 *  Created on: 08.06.2017
 *      Author: aca592
 */

#include "TestPuckStateMachine.h"

SETUP(TestPuckStateMachine) {
	REG_TEST(test1, 1, "Test the longest path");
	REG_TEST(test2, 2, "Test all Warning transitions");
	return 1;
}

BEFORE_TC(TestPuckStateMachine) {
	uint16_t puckID = 1;
	context = new PuckContext(puckID);
	return 1;
}

AFTER_TC(TestPuckStateMachine) {
	delete context;
	return 1;
}

BEFORE(TestPuckStateMachine) {
	return 1;
}

AFTER(TestPuckStateMachine) {
	return 1;
}
#if !machine
TEST_IMPL(TestPuckStateMachine, test1) {
	PuckSignal::Signal signal;
	PuckSignal::Return returnVal;
	//State: Inlet -> InletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State: InletArea -> InletTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State: InletTimer -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::HEIGHT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	signal.heightSignal.ID = SignalID::NORMAL_ID;


	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().heightType.ID != SignalID::NORMAL_ID){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> MeasurementArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementArea -> MeasurementTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementTimer -> MetalType
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::METAL_DETECT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().metal != 1){
		return TEST_FAILED;
	}

	//State MetalType -> TypeKnown
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::EVALUATE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State TypeKnwon -> SwitchArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_OPEN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchArea -> SwitchTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchTimer -> OutletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::SEND && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State OutletArea -> InTransfer
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::ACCEPT_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State InTransfer -> TransferStopped
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::STOP_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::STOP){
		return TEST_FAILED;
	}

	//State TransferStopped -> InTransfer
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::RESUME_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State InTransfer -> Transferred
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State Transferred -> death
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::RECEIVED_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::DELETE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	return TEST_PASSED;
}
#else
TEST_IMPL(TestPuckStateMachine, test1) {
	PuckSignal::Signal signal;
	PuckSignal::Return returnVal;
	//State: TransferArea -> TransferTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State: TransferTimer -> Inlet
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: Inlet -> InletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: InletArea -> InletTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: InletTimer -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::HEIGHT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State Heightmeasurement -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	signal.heightSignal.ID = SignalID::NORMAL_ID;


	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().heightType.ID != SignalID::NORMAL_ID){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> MeasurementArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementArea -> MeasurementTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementTimer -> MetalType
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::METAL_DETECT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().metal != 1){
		return TEST_FAILED;
	}

	//State MetalType -> TypeKnown
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::EVALUATE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State TypeKnwon -> SwitchArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_OPEN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchArea -> SwitchTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchTimer -> OutletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::STOP){
		return TEST_FAILED;
	}

	//State OutletArea -> death
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::DELETE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	return TEST_PASSED;
}
#endif
#if !machine
TEST_IMPL(TestPuckStateMachine, test2) {
	PuckSignal::Signal signal;
	PuckSignal::Return returnVal;
	//State: Inlet -> InletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State: InletArea -> InletTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State: InletTimer -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::HEIGHT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	signal.heightSignal.ID = SignalID::NORMAL_ID;


	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().heightType.ID != SignalID::NORMAL_ID){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> MeasurementArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementArea -> MeasurementTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementTimer -> MetalType
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::METAL_DETECT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().metal != 1){
		return TEST_FAILED;
	}

	//State MetalType -> TypeKnown
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::EVALUATE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State TypeKnwon -> SwitchArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_OPEN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchArea -> SwitchTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchTimer -> OutletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::SEND && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State OutletArea -> InTransfer
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::ACCEPT_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State InTransfer -> TransferStopped
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::STOP_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::STOP){
		return TEST_FAILED;
	}

	//State TransferStopped -> InTransfer
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::RESUME_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State InTransfer -> Transferred
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State Transferred -> death
	signal.signalType = PuckSignal::SignalType::SERIAL_SIGNAL;
	signal.serialSignal = Serial_n::ser_proto_msg::RECEIVED_SER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::DELETE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	return TEST_PASSED;
}
#else
TEST_IMPL(TestPuckStateMachine, test2) {
	PuckSignal::Signal signal;
	PuckSignal::Return returnVal;
	//State: TransferArea -> TransferTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State: TransferTimer -> Inlet
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: Inlet -> InletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::INLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: InletArea -> InletTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State: InletTimer -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::HEIGHT && returnVal.puckSpeed != PuckSignal::PuckSpeed::SLOW){
		return TEST_FAILED;
	}

	//State Heightmeasurement -> Heightmeasurement
	signal.signalType = PuckSignal::SignalType::HEIGHT_SIGNAL;
	signal.heightSignal.ID = SignalID::NORMAL_ID;


	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().heightType.ID != SignalID::NORMAL_ID){
		return TEST_FAILED;
	}
	//State Heightmeasurement -> MeasurementArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::HEIGHTMEASUREMENT_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementArea -> MeasurementTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//State MeasurementTimer -> MetalType
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::METAL_DETECT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}
	//check if Type correct
	if(context->getType().metal != 1){
		return TEST_FAILED;
	}

	//State MetalType -> TypeKnown
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::EVALUATE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State TypeKnwon -> SwitchArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::SWITCH_OPEN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchArea -> SwitchTimer
	signal.signalType = PuckSignal::SignalType::TIMER_SIGNAL;
	signal.timerSignal.puckID = context->getPuckID();
	signal.timerSignal.type = PuckSignal::TimerType::EARLY_TIMER;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	//State SwitchTimer -> OutletArea
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_IN;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::ACCEPT && returnVal.puckSpeed != PuckSignal::PuckSpeed::STOP){
		return TEST_FAILED;
	}

	//State OutletArea -> death
	signal.signalType = PuckSignal::SignalType::INTERRUPT_SIGNAL;
	signal.interruptSignal = interrupts::interruptSignals::OUTLET_OUT;

	returnVal = context->process(signal);
	if(returnVal.puckReturn != PuckSignal::PuckReturn::DELETE && returnVal.puckSpeed != PuckSignal::PuckSpeed::FAST){
		return TEST_FAILED;
	}

	return TEST_PASSED;
}
#endif
