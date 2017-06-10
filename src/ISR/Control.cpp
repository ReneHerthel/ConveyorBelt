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
//#include "ConveyorBeltService.h"
//#include "ConveyorBeltState.h"
//#include "SortingSwitchService.h"
#include "Signals.h"

using namespace std;
using namespace interrupts;


//ConveyorBeltService service; this was for testing only
//SortingSwitchService service1;

Control::Control(){
}

Control::Control(const int chid):
	chid_(chid),
	sender(new PulseMessageSenderService(chid)){

}

Control::~Control(){
}

int code = 5;



void Control::lightBarrier_ENTRY_IN(){

	sender->sendPulseMessage(code, INLET_IN);

	//service.ConveyorBeltChangeState(RIGHTFAST);
	//out8(0x300, (in8(0x300) | 1 << 0));
	cout << "Control Entry_IN" << endl;

}

void Control::lightBarrier_ENTRY_OUT(){

	sender->sendPulseMessage(code, INLET_OUT);

	cout << "Control Entry_OUT" << endl;

}

void Control::lightBarrier_HEIGHT_IN(){

	sender->sendPulseMessage(code, HEIGHTMEASUREMENT_IN);

	//service.ConveyorBeltChangeState(RIGHTSLOW);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control Height_IN" << endl;

}

void Control::lightBarrier_HEIGHT_OUT(){

	sender->sendPulseMessage(code, HEIGHTMEASUREMENT_OUT);

	//service.ConveyorBeltChangeState(RIGHTFAST);
	cout << "Control Height_OUT" << endl;
}

void Control::height(){

	//service.ConveyorBeltChangeState(RIGHTSLOW);
	//out8(0x300, (in8(0x300) | 1 << (0 | 2)));
	cout << "Control sensorHeight" << endl;
}

void Control::lightBarrier_SWITCH_IN(){

	sender->sendPulseMessage(code, SWITCH_IN);

	cout << "Control Switch_IN" << endl;

}
void Control::lightBarrier_SWITCH_OUT(){

	sender->sendPulseMessage(code, SWITCH_OUT);

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//service1.sortingSwitchClose();
	cout << "Control Switch_OUT" << endl;

}
void Control::metal(){

	sender->sendPulseMessage(code, METAL_DETECT);

	//service1.sortingSwitchOpen();
	cout << "Control METAL" << endl;

}

void Control::lightBarrier_RAMP_IN(){

	sender->sendPulseMessage(code, SLIDE_IN);

	cout << "Control Ramp_IN" << endl;

}

void Control::lightBarrier_RAMP_OUT(){

	sender->sendPulseMessage(code, SLIDE_OUT);

	//service.ConveyorBeltChangeState(STOP);
	cout << "Control Ramp_OUT" << endl;

}

void Control::lightBarrier_EXIT_IN(){

	sender->sendPulseMessage(code, OUTLET_IN);

	//service.ConveyorBeltChangeState(STOP);
	cout << "Control EXIT_IN" << endl;

}
void Control::lightBarrier_EXIT_OUT(){

	sender->sendPulseMessage(code, OUTLET_OUT);

	cout << "Control EXIT_OUT" << endl;

}

void Control::b_Start(){

	sender->sendPulseMessage(code, BUTTON_START);

	//service.ConveyorBeltChangeState(RIGHTFAST);
	//out8(0x300, (in8(0x300) | 1 << 0));
	cout << "Control buttonStart" << endl;
}

void Control::b_STOP(){

	sender->sendPulseMessage(code, BUTTON_STOP);

	//service.ConveyorBeltChangeState(STOP);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control buttonStop" << endl;

}

void Control::b_EStop(){

	sender->sendPulseMessage(code, BUTTON_ESTOP);

	//service1.sortingSwitchClose();
	//service.ConveyorBeltChangeState(STOP);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control buttonEStop" << endl;
}

void Control::b_Reset(){

	sender->sendPulseMessage(code, BUTTON_RESET);

	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control buttonReset" << endl;
}
void Control::switchen(){

	sender->sendPulseMessage(code, SWITCH_OPEN);

	cout << "Control SWITCH-OPEN" << endl;
}




