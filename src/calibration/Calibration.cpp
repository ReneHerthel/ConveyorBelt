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

	cbs.changeState(STOP);


	//CENTER THE PUCK AND CALC TIME FOR RUNNING THROUGH A LB
	while(!pollLB(LB_ENTRY));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cbs.changeState(RIGHTFAST);

	while(!pollLB(LB_HEIGHT));
	auto lb_in = system_clock::now();
	while(pollLB(LB_HEIGHT));
	auto lb_out = system_clock::now();

	milliseconds lb_throughput = duration_cast<milliseconds>(lb_out - lb_in);

	cbs.changeState(LEFTFAST);
	while(!pollLB(LB_ENTRY));
	cbs.changeState(STOP);

	for(int i = 0; i < 2; i++){
		while(!pollLB(LB_ENTRY));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if(i == 0) 	cbs.changeState(RIGHTFAST);
		else		cbs.changeState(RIGHTSLOW);

		while(!pollLB(LB_ENTRY));
		auto start = system_clock::now();

		auto last_lb = system_clock::now();

		while(!pollLB(LB_HEIGHT));
		heightMeasure[i] = milliseconds(duration_cast<milliseconds>(system_clock::now() - last_lb));
		sss.sortingSwitchOpen();
		while(pollLB(LB_HEIGHT));
		start = system_clock::now();

		while(!pollLB(LB_SWITCH));
		sortingSwitch[i] = duration_cast<milliseconds>(system_clock::now()  - last_lb);
		while(pollLB(LB_HEIGHT));
		start = system_clock::now();

		while(!pollLB(LB_EXIT));
		outlet[i] = duration_cast<milliseconds>(system_clock::now() - last_lb);
		overall[i] = duration_cast<milliseconds>(system_clock::now() - start);

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

	slowToFastFactor = (double)overall[0].count() / (double)overall[1].count();
	slowToFastFactor = (double)overall[1].count() / (double)overall[0].count();

}


Calibration& Calibration::getInstance(){
	static Calibration instance;
	return instance;
}

using namespace DistanceSpeed;

uint32_t Calibration::getCalibration(DistanceSpeed::lb_distance distance, DistanceSpeed::speed_t speed){
	int slowOrFast = 0;
	switch(speed){
		case FAST: slowOrFast = 0; break;
		case SLOW: slowOrFast = 1; break;
		case DistanceSpeed::STOP: return 0;
	}

	switch(distance){
		case INLET_TO_HEIGHT:	return heightMeasure[slowOrFast].count();
		case HEIGHT_TO_SWITCH:  return sortingSwitch[slowOrFast].count();
		case SWITCH_TO_OUTLET: 	return outlet[slowOrFast].count();
		case OUT_TO_IN:			return inlet[slowOrFast].count();
	}

}

bool Calibration::pollLB(sensor_t sensor){
	return((in8(PORTB_ADDR) & sensor) == 0);
}


Calibration::Calibration(){}
Calibration::~Calibration(){}
