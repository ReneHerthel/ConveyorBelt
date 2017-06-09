/*
 * isr_pulse.cpp
 *
 *  Created on: 27.04.2017 based on tutorium-example
 *      Author: abt674
 */

#include <iostream>
#include <cstdlib>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include "ConveyorBelt-devel/src/HWaccess.h"

using namespace std;

int isrId = 0;
int isrChannel = 0;
int isrConnection = 0;
struct sigevent isrEvent;
int altval = 41162;

// ISR (c-Function)
const struct sigevent* ISR_DIO(void* arg, int id) {
    struct sigevent* event = (struct sigevent*) arg;
    out8(0x30F, 0);

    event->sigev_notify = SIGEV_PULSE ;
    event->__sigev_un1.__sigev_coid = isrConnection;
    event->__sigev_un2.__st.__sigev_code = 0;
    event->sigev_value.sival_int = in8(0x301) | (in8(0x302) << 8);
    return event;
}

//ISR anmelden
void registerISR(void){
    out8(0x30F, 0);
    out8(0x30B, 0b11111101);
    out8(0x30B, 0b11111001);

    SIGEV_PULSE_INIT(&isrEvent, isrConnection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
    isrId = InterruptAttach(11, ISR_DIO, &isrEvent, sizeof(isrEvent), 0);
    if (isrId == -1) {
        exit(EXIT_FAILURE);
    }
}

//nach thread ende isr abmelden
void unregisterISR(void){
    if( InterruptDetach(isrId) == -1 ){
        exit(EXIT_FAILURE);
    }
    out8(0x30B, 0b11111111);
    out8(0x30F,0);
}



int main() {
    // Init and Register ISR
    if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
        exit(EXIT_FAILURE);
    }
    //create a channel to receive pulses
    if (( isrChannel = ChannelCreate(0)) == -1){
        exit(EXIT_FAILURE);
    }
    //connect isr to channel
    if ((isrConnection = ConnectAttach(0, 0, isrChannel, 0, 0)) == -1){
        exit(EXIT_FAILURE);
    }

    // Register Interrupt Service Routine
    registerISR();

    struct _pulse pulse;

    // Wait for Pulse Message
    do{
    	//pulse message empfangen(warten)
        MsgReceivePulse(isrChannel,&pulse,sizeof(pulse),NULL);

        //register zuordnen
        int diff = pulse.value.sival_int ^ altval;
        // Print received Pulse message Value
        cout << "Got an Interrupt, value: " << pulse.value.sival_int << " " << diff << endl;
        altval =  pulse.value.sival_int;

    }while(1);

    // Cleanup
    unregisterISR();
    //isr verbindung aufheben
    if( ConnectDetach(isrConnection) == -1){
        exit(EXIT_FAILURE);
    }
    //channel löschen
    if( ChannelDestroy(isrChannel) == -1 ){
        exit(EXIT_FAILURE);
    }

    return 0;
}
