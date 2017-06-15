/*
 * Name        : control
 * Author      : abt674
 * Version     : 0.5
 * Copyright   : none
 */

#include <iostream>
#include <unistd.h>
#include "Control.h"
#include <chrono>
#include <thread>
#include "HWaccess.h"
#include "Signals.h"

using namespace std;
using namespace interrupts;
using namespace rcv;

Control::Control() {
    // Nothing todo so far.
}

/*
 * Call this constructor to get a interrupt-signal
 *
 * @param [chid] channel id to receive the pulsemessage
 * */
Control::Control(const int chid)
    :    chid_(chid)
    ,    sender(new PulseMessageSenderService(chid)) {
    // Nothing todo so far.
}

Control::~Control() {
    // Nothing todo so far.
}

int code = 5;

/*
 * functions called by ISR-class, just send a new pulsemessage to maincontroller
 * */
void Control::lightBarrier_ENTRY_IN() {
    sender->sendPulseMessage(code, INLET_IN);
    cout << "Control Entry_IN "  << endl;
}

void Control::lightBarrier_ENTRY_OUT() {
    sender->sendPulseMessage(code, INLET_OUT);
    cout << "Control Entry_OUT" << endl;
}

void Control::lightBarrier_HEIGHT_IN() {
    sender->sendPulseMessage(code, HEIGHTMEASUREMENT_IN);
    cout << "Control Height_IN" << endl;
}

void Control::lightBarrier_HEIGHT_OUT() {
    sender->sendPulseMessage(code, HEIGHTMEASUREMENT_OUT);
    cout << "Control Height_OUT" << endl;
}

void Control::height() {
    cout << "Control sensorHeight" << endl;
}

void Control::lightBarrier_SWITCH_IN() {
    sender->sendPulseMessage(code, SWITCH_IN);
    cout << "Control Switch_IN" << endl;
}
void Control::lightBarrier_SWITCH_OUT() {
    sender->sendPulseMessage(code, SWITCH_OUT);
    cout << "Control Switch_OUT" << endl;
}
void Control::metal() {
    sender->sendPulseMessage(code, METAL_DETECT);
    cout << "Control METAL" << endl;
}

void Control::lightBarrier_RAMP_IN() {
    sender->sendPulseMessage(code, SLIDE_IN);
    cout << "Control Ramp_IN" << endl;
}

void Control::lightBarrier_RAMP_OUT() {
    sender->sendPulseMessage(code, SLIDE_OUT);
    cout << "Control Ramp_OUT" << endl;
}

void Control::lightBarrier_EXIT_IN() {
    sender->sendPulseMessage(code, OUTLET_IN);
    cout << "Control EXIT_IN" << endl;
}
void Control::lightBarrier_EXIT_OUT() {
    sender->sendPulseMessage(code, OUTLET_OUT);
    cout << "Control EXIT_OUT" << endl;
}

void Control::b_Start() {
    sender->sendPulseMessage(code, BUTTON_START);
    cout << "Control buttonStart" << endl;
}

void Control::b_STOP() {
    sender->sendPulseMessage(code, BUTTON_STOP);
    cout << "Control buttonStop" << endl;
}

void Control::b_EStop() {
    sender->sendPulseMessage(code, BUTTON_ESTOP);
    cout << "Control buttonEStop" << endl;
}

void Control::b_Reset() {
    sender->sendPulseMessage(code, BUTTON_RESET);
    cout << "Control buttonReset" << endl;
}
void Control::switchen() {
    sender->sendPulseMessage(code, SWITCH_OPEN);
    cout << "Control SWITCH-OPEN" << endl;
}
