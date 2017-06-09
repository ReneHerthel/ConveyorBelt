/*
 * Calibration.cpp
 *
 *  Created on: 09.06.2017
 *      Author: aca619
 */

#include "Calibration.h"
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <stdlib.h>
#include <iostream.h>
#include <hw/inout.h>
#include "Logger.h"
#include "ConveyorBeltState.h"
#include "ConveyorBeltService.h"
#include "SortingSwitchService.h"
#include <thread>

using namespace chrono;

void Calibration::calibrate(void){
	ConveyorBeltService cbs;
    SortingSwitchService sss;

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
			LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
			return;
	}

	LOG_DEBUG << "GOT HW ACCESS" << std::endl;



	//CENTER THE PUCK
	while(!pollLB(LB_ENTRY));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cbs.changeState(RIGHTFAST);
	while(!pollLB(LB_HEIGHT));
	cbs.changeState(LEFTFAST);
	while(!pollLB(LB_ENTRY));
	cbs.changeState(STOP);

	for(int i = 0; i < 2; i++){
		while(!pollLB(LB_ENTRY));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if(i == 0) 	cbs.changeState(RIGHTFAST);
		else		cbs.changeState(RIGHTSLOW);

		while(pollLB(LB_ENTRY));

		auto start = system_clock::now();

		while(!pollLB(LB_HEIGHT));
		heightMeasure[i] = milliseconds(duration_cast<milliseconds>(system_clock::now() - start));
		sss.sortingSwitchOpen();

		while(!pollLB(LB_SWITCH));
		sortingSwitch[i] = duration_cast<milliseconds>(system_clock::now()  - start) - heightMeasure[i];


		while(!pollLB(LB_EXIT));
		outlet[i] = duration_cast<milliseconds>(system_clock::now() - start) - heightMeasure[i] - sortingSwitch[i];
		cbs.changeState(STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		cbs.changeState(LEFTFAST);
		while(!pollLB(LB_HEIGHT));
		sss.sortingSwitchClose();
		while(!pollLB(LB_ENTRY));
		cbs.changeState(STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	sss.sortingSwitchClose(); //Safety


}


bool Calibration::pollLB(sensor_t sensor){
	return((in8(PORTB_ADDR) & sensor) == 0);
}
