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

void Calibration::calibrate(void){
	ConveyorBeltService cbs;
    SortingSwitchService sss;

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
			LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
			return;
	}

	LOG_DEBUG << "GOT HW ACCESS" << std::endl;


	for(int i = 0; i < 2; i++){
		while(!pollLB(LB_ENTRY));
		if(i == 0) 	cbs.changeState(RIGHTFAST);
		else		cbs.changeState(RIGHTSLOW);

		while(pollLB(LB_ENTRY));

		auto start = std::chrono::system_clock::now;

		while(!pollLB(LB_HEIGHT));
		heightMeasure[i] = std::chrono::system_clock::now - start;

		while(!pollLB(LB_SWITCH));
		sss.sortingSwitchOpen();
		sortingSwitch[i] = std::chrono::system_clock::now - heightMeasure[i] - start;


		while(!pollLB(LB_EXIT));
		outlet[i] = td::chrono::system_clock::now - heightMeasure[i] - sortingSwitch[i] - start;
		cbs.changeState(STOP);

		cbs.changeState(LEFTFAST);
	}


}


bool Calibration::pollLB(sensor_t sensor){
	return((in8(PORTB_ADDR) & sensor) == 0);
}
