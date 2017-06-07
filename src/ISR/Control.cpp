/*
 * Name        : control
 * Author      : abt674
 * Version     : 0.3
 * Copyright   : none
 */


#include <iostream>
#include <unistd.h>
#include "Control.h"
#include <chrono>
#include <thread>
#include "HWaccess.h"
#include "ConveyorBeltService.h"
#include "ConveyorBeltState.h"
#include "SortingSwitchService.h"


using namespace std;

ConveyorBeltService service;
SortingSwitchService service1;

void Control::LightBarrier_ENTRY_IN(){

	service.ConveyorBeltChangeState(RIGHTFAST);
	//out8(0x300, (in8(0x300) | 1 << 0));
	cout << "Control Entry_IN" << endl;

}

void Control::LightBarrier_ENTRY_OUT(){
	cout << "Control Entry_OUT" << endl;

}

void Control::LightBarrier_HEIGHT_IN(){
	//service.ConveyorBeltChangeState(RIGHTSLOW);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control Height_IN" << endl;

}

void Control::LightBarrier_HEIGHT_OUT(){
	service.ConveyorBeltChangeState(RIGHTFAST);
	cout << "Control Height_OUT" << endl;
}

void Control::HEIGHT(){
	//service.ConveyorBeltChangeState(RIGHTSLOW);
	out8(0x300, (in8(0x300) | 1 << (0 | 2)));
	cout << "Control sensorHeight" << endl;
}

void Control::LightBarrier_SWITCH_IN(){
	cout << "Control Switch_IN" << endl;

}
void Control::LightBarrier_SWITCH_OUT(){
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	service1.sortingSwitchClose();
	cout << "Control Switch_OUT" << endl;

}
void Control::METAL(){
	service1.sortingSwitchOpen();
	cout << "Control METAL" << endl;

}

void Control::LightBarrier_RAMP_IN(){
	cout << "Control Ramp_IN" << endl;

}

void Control::LightBarrier_RAMP_OUT(){
	service.ConveyorBeltChangeState(STOP);
	cout << "Control Ramp_OUT" << endl;

}

void Control::LightBarrier_EXIT_IN(){
	service.ConveyorBeltChangeState(STOP);
	cout << "Control EXIT_IN" << endl;

}
void Control::LightBarrier_EXIT_OUT(){
	cout << "Control EXIT_OUT" << endl;

}

void Control::B_Start(){
	service.ConveyorBeltChangeState(RIGHTFAST);
	//out8(0x300, (in8(0x300) | 1 << 0));
	cout << "Control buttonStart" << endl;
}

void Control::B_STOP(){
	service.ConveyorBeltChangeState(STOP);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control buttonStop" << endl;

}

void Control::B_EStop(){
	service1.sortingSwitchClose();
	service.ConveyorBeltChangeState(STOP);
	//out8(0x300, (in8(0x300) & ~(0x0F)));
	cout << "Control buttonEStop" << endl;
}

void Control::B_Reset(){
	//out8(0x300, (in8(0x300) & ~(0x0F)));

	cout << "Control buttonReset" << endl;
}
void Control::SWITCH(){
	cout << "Control SWITCH-OPEN" << endl;
}



Control::Control(){

}

Control::~Control(){
}
