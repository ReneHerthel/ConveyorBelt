                                                                         /*
 * ISR.cpp
 *
 *  Created on: 27.04.2017 based on tutorium-example
 *      Author: abt674
 */

#include <iostream>
#include <cstdlib>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include "HWaccess.h"
#include "Control.h"
#include "ISR.h"

using namespace std;

int isrId = 0;
int isrChannel = 0;
int isrConnection = 0;
struct sigevent isrEvent;
int portbc = 0;
Control * ctrl;


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
void registerISR(void) {
    //Lichtschranken und Sensoren
    out8(0x30F, 0);
    out8(0x30B, 0b11111101);
    //Buttons
    out8(0x30B, 0b11111001);

    SIGEV_PULSE_INIT(&isrEvent, isrConnection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
    isrId = InterruptAttach(11, ISR_DIO, &isrEvent, sizeof(isrEvent), 0);

    if (isrId == -1) {
        exit(EXIT_FAILURE);
    }
}

//nach Thread Ende ISR abmelden
void unregisterISR(void) {

    if (InterruptDetach(isrId) == -1 ) {
        exit(EXIT_FAILURE);
    }

    out8(0x30B, 0b11111111);
    out8(0x30F,0);
}

/*
 * Creates the ISR-Channel
 * @param [control] Control Object for Methodcalls
 * */
ISR::ISR(Control * control) {
    cout << "ctor: ISR_Thread" << endl;
    ctrl = control;

    if ((isrChannel = ChannelCreate(0)) == -1) {
        exit(EXIT_FAILURE);
    }

    cout<< "isrchannel " << isrChannel <<endl;

    if ((isrConnection = ConnectAttach(0, 0, isrChannel, 0, 0)) == -1) {
        exit(EXIT_FAILURE);
    }
}
/*
 * deconstructor
 * */
ISR::~ISR() {
    cout << "dtor: ISR_Thread" << endl;
}
/*
 * "main"-function, call this to start the ISR
 * this function registers the ISR and determines the origin of an interrupt
 * */
void ISR::operator()() {
    bool running = true;

    // Init and Register ISR
    if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
        exit(EXIT_FAILURE);
    }
    // Register Interrupt Service Routine
    registerISR();

    struct _pulse pulse;

    portbc = in8(0x301) | (in8(0x302) << 8);

    // Wait for Pulse Message
    do {
        //pulse message empfangen(warten)
        MsgReceivePulse(isrChannel,&pulse,sizeof(pulse),NULL);

        //register zuordnen
        int diff = pulse.value.sival_int ^ portbc;
        portbc =  pulse.value.sival_int;

		if((diff & BUTTONESTOP) == BUTTONESTOP){
			if ((portbc & BUTTONESTOP) == BUTTONESTOP) {
				//running = true;
				ctrl->b_EStop();
			} else {
				//cout << "button_estop_released: " << endl;
				//running = false;
			}
		}
		else if((diff & LightBarrier_HEIGHT) == LightBarrier_HEIGHT){
				if ((portbc & LightBarrier_HEIGHT) == LightBarrier_HEIGHT) {
					ctrl->lightBarrier_HEIGHT_OUT();
				} else {
					//cout << "LightBarrier_height" << endl;
					ctrl->lightBarrier_HEIGHT_IN();
				}
		}
		else  if((diff & LightBarrier_SWITCH) == LightBarrier_SWITCH){
				if ((portbc &LightBarrier_SWITCH) == LightBarrier_SWITCH){
					ctrl->lightBarrier_SWITCH_OUT();
				} else {
					//cout << "LightBarrier_switch" << endl;
					ctrl->lightBarrier_SWITCH_IN();
				}
		}
		else if((diff & LightBarrier_RAMP) == LightBarrier_RAMP){
				if ((portbc &LightBarrier_RAMP) == LightBarrier_RAMP) {
					ctrl->lightBarrier_RAMP_OUT();
				} else {
					//cout << "LightBarrier_ramp" << endl;
					ctrl->lightBarrier_RAMP_IN();
				}
		}
		else if((diff & LightBarrier_EXIT) == LightBarrier_EXIT){
				if ((portbc & LightBarrier_EXIT) == LightBarrier_EXIT ) {
					//cout << "LightBarrier_exit_OUT" << endl;
					ctrl->lightBarrier_EXIT_OUT();
				} else {
					//cout << "LightBarrier_exit_IN" << endl;
					ctrl->lightBarrier_EXIT_IN();
				}
			}
		else if((diff & BUTTONSTART) == BUTTONSTART){
				if ((portbc & BUTTONSTART) == BUTTONSTART) {
					//cout << "button_start_pressed" << endl;
					ctrl->b_Start();
				} else {
					//cout << "button_start_released" << endl;
				}
		}
		else if((diff & BUTTONSTOP) == BUTTONSTOP){
				if ((portbc &BUTTONSTOP) == BUTTONSTOP) {
					//cout << "button_stop_pressed" << endl;
					ctrl->b_STOP();
				} else {
					//cout << "button_stop_released" << endl;
				}
		}
		else if((diff & BUTTONRESET) == BUTTONRESET){
				if ((portbc &BUTTONRESET) == BUTTONRESET) {
					//cout << "button_reset_pressed" << endl;
					ctrl->b_Reset();
				} else {
					//cout << "button_reset_released" << endl;

				}
		}
		else if ((diff & LightBarrier_ENTRY) == LightBarrier_ENTRY){
			if ((portbc & LightBarrier_ENTRY) == LightBarrier_ENTRY) {
				//cout << "LightBarrier_entry_OUT " << endl;
				ctrl->lightBarrier_ENTRY_OUT();
			} else {
				//cout << "LightBarrier_entry_IN " << endl;
				ctrl->lightBarrier_ENTRY_IN();
			}
	}
		else if ((diff & SENSOR_METAL) == SENSOR_METAL){
		        if ((portbc & SENSOR_METAL) == SENSOR_METAL) {
		        	//cout << "metal_in" << endl;
	        		ctrl->metal();
		        	} else {
		        		//cout << "metal_isOutofSensor" << endl;
		        }
		}
		/*else if ((diff & SENSOR_HEIGHT) == SENSOR_HEIGHT){
				if ((portbc & SENSOR_HEIGHT) == SENSOR_HEIGHT) {
					cout << "sensor_height" << endl;
					ctrl->height();

				} else {

				}
		}*/
		else if ((diff & SWITCH_OPEND) == SWITCH_OPEND){
				if ((portbc & SWITCH_OPEND) == SWITCH_OPEND) {
					//cout << "openSwitch " << endl;
					ctrl->switchopen();
				} else {
					//cout << "closeSwitch" << endl;
					ctrl->switchclosed();
				}
		}

    } while (running);

    cout << "Shutdown ISR..."<<endl;

    // Cleanup
    unregisterISR();

    //isr verbindung aufheben
    if (ConnectDetach(isrConnection) == -1) {
        exit(EXIT_FAILURE);
    }

    //channel loeschen
    if (ChannelDestroy(isrChannel) == -1 ) {
        exit(EXIT_FAILURE);
    }

    cout << "ISR detached and channel destroyed!" << endl;
  }
