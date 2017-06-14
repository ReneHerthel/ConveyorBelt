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

bool button_start_active = true;
bool button_stop_active = true;
bool button_reset_active = true;
bool button_estop_active = true;
bool lb_entry_active = true;
bool lb_exit_active = true;
bool lb_height_active = true;
bool lb_ramp_active = true;
bool lb_switch_active = true;
bool sensor_height_active = true;
bool sensor_metal_active = true;
bool switch_open = true;




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
void unregisterISR(void){
    if( InterruptDetach(isrId) == -1 ){
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
void ISR::operator()(){
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
    do{
    	//pulse message empfangen(warten)
        MsgReceivePulse(isrChannel,&pulse,sizeof(pulse),NULL);


        //register zuordnen
        int diff = pulse.value.sival_int ^ portbc;
        portbc =  pulse.value.sival_int;


        			if((diff & BUTTONESTOP) == BUTTONESTOP){

    					if (button_estop_active) {
    						cout << "button_estop" << endl;
    						ctrl->b_EStop();
    						button_estop_active = false;
    						running = false;
    					} else {
    						button_estop_active = true;
    					}
					}

        			else if((diff & LightBarrier_HEIGHT) == LightBarrier_HEIGHT){
        					if (lb_height_active) {
        						cout << "LightBarrier_height" << endl;
        						ctrl->lightBarrier_HEIGHT_IN();
        						lb_height_active = false;
        					} else {
        						lb_height_active = true;
        						ctrl->lightBarrier_HEIGHT_OUT();
        					}
        			}

        			else  if((diff & LightBarrier_SWITCH) == LightBarrier_SWITCH){
        					if (lb_switch_active){
        						cout << "LightBarrier_switch" << endl;
        						ctrl->lightBarrier_SWITCH_IN();
        						lb_switch_active = false;
        					} else {
        						ctrl->lightBarrier_SWITCH_OUT();
        						lb_switch_active = true;
        					}
        			}

        			else if((diff & LightBarrier_RAMP) == LightBarrier_RAMP){
        					if (lb_ramp_active) {
        						cout << "LightBarrier_ramp" << endl;
        						ctrl->lightBarrier_RAMP_IN();
        						lb_ramp_active = false;
        					} else {
        						ctrl->lightBarrier_RAMP_OUT();
        						lb_ramp_active = true;
        					}
        			}

    				else if((diff & LightBarrier_EXIT) == LightBarrier_EXIT){
        					if (lb_exit_active) {
        						cout << "LightBarrier_exit" << endl;
        						ctrl->lightBarrier_EXIT_IN();
        						lb_exit_active = false;
        					} else {
        						ctrl->lightBarrier_EXIT_OUT();
        						lb_exit_active = true;
        					}
    					}

    				else if((diff & BUTTONSTART) == BUTTONSTART){
        					if (button_start_active) {
        						cout << "button_start" << endl;
        						ctrl->b_Start();
        						button_start_active = false;
        					} else {
        						button_start_active = true;
        					}
        			}

    				else if((diff & BUTTONSTOP) == BUTTONSTOP){
        					if (button_stop_active) {
        						cout << "button_stop" << endl;
        						ctrl->b_STOP();
        						button_stop_active = false;
        					} else {
        						button_stop_active = true;
        					}
        			}

    				else if((diff & BUTTONRESET) == BUTTONRESET){
        					if (button_reset_active) {
        						cout << "button_reset" << endl;
        						ctrl->b_Reset();
        						button_reset_active = false;
        					} else {
        						button_reset_active = true;
        					}
        			}

    				else if ((diff & LightBarrier_ENTRY) == LightBarrier_ENTRY){
    					if (lb_entry_active) {
    						cout << "LightBarrier_entry_" << endl;
    						ctrl->lightBarrier_ENTRY_IN();
    						lb_entry_active = false;
    					} else {
    						lb_entry_active = true;
    						ctrl->lightBarrier_ENTRY_OUT();
    					}
    			}

    				else if ((diff & SENSOR_METAL) == SENSOR_METAL){
        			        if (sensor_metal_active) {
        			        	cout << "metal" << endl;
        			        	ctrl->metal();
        			        	sensor_metal_active = false;
        			        	} else {
        			        	cout << "no_metal" << endl;
        			            sensor_metal_active = true;
        			        }
        			}

    				else if ((diff & SENSOR_HEIGHT) == SENSOR_HEIGHT){
        					if (sensor_height_active) {
        						cout << "sensor_height" << endl;
        						ctrl->height();
        						sensor_height_active = false;
        					} else {
        						sensor_height_active = true;
        					}
        			}

    				else if ((diff & SWITCH_OPEND) == SWITCH_OPEND){
        					if (switch_open) {
        						cout << "switch is open" << endl;
        						ctrl->switchen();
        						switch_open = false;
        					} else {
        						cout << "switch is closed" << endl;
        						switch_open = true;
        					}
        			}


    }while(running);

    cout << "Shutdown ISR..."<<endl;
    // Cleanup
    unregisterISR();
    //isr verbindung aufheben
    if( ConnectDetach(isrConnection) == -1){
        exit(EXIT_FAILURE);
    }
    //channel l�schen
    if( ChannelDestroy(isrChannel) == -1 ){
        exit(EXIT_FAILURE);
    }
    cout << "ISR detached and channel destroyed!" << endl;
	}





