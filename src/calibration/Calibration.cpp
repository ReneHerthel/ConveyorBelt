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
#include <thread>
#include "HeightMeasurementService.h"
#include "HeightMeasurementHal.h"

using namespace chrono;

void Calibration::calibrate(void){
	ConveyorBeltService cbs;
    SortingSwitchService sss;

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
			LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
			return;
	}

	LOG_DEBUG << "GOT HW ACCESS" << std::endl;

	cbs.changeState(ConveyorBeltState::STOP);


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
	cbs.changeState(ConveyorBeltState::STOP);

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
		last_lb = system_clock::now();

		while(!pollLB(LB_SWITCH));
		sortingSwitch[i] = duration_cast<milliseconds>(system_clock::now()  - last_lb);
		while(pollLB(LB_HEIGHT));
		last_lb = system_clock::now();

		while(!pollLB(LB_EXIT));
		outlet[i] = duration_cast<milliseconds>(system_clock::now() - last_lb);
		overall[i] = duration_cast<milliseconds>(system_clock::now() - start);

		cbs.changeState(ConveyorBeltState::STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		cbs.changeState(LEFTFAST);
		while(!pollLB(LB_HEIGHT));
		sss.sortingSwitchClose();
		while(!pollLB(LB_ENTRY));
		cbs.changeState(ConveyorBeltState::STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	sss.sortingSwitchClose(); //Safety

	slowToFastFactor = (double)overall[0].count() / (double)overall[1].count();
	fastToSlowFactor = (double)overall[1].count() / (double)overall[0].count();

}

void  Calibration::calibrateHeighMeasurement(void){

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
			LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
			return;
	}

	HeightMeasurementHal hhal;
	uint16_t data = 0;

	hhal.read(data);

	hmCal.refHeight = data; //Belt height


	hmCal.surfaceHeight = CALC_ABS_HEIGHT(data, SURFACE);
	hmCal.holeHeight 	= CALC_ABS_HEIGHT(data, HOLE);
	hmCal.highHeight	= CALC_ABS_HEIGHT(data, LOGICAL_1);
	hmCal.lowHeight		= CALC_ABS_HEIGHT(data, LOGICAL_0);
	hmCal.invalidHeight = CALC_ABS_HEIGHT(data, INVALID);
	hmCal.delta = DELTA;

}

HeightMeasurementService::CalibrationData Calibration::getHmCalibration(void){
	return hmCal;
}


void Calibration::manualCalibration(uint32_t hf, uint32_t hs, uint32_t sf, uint32_t ss, uint32_t of, uint32_t os, uint32_t ovf, uint32_t ovs){
	//heightMeasure[0] += ((long long int)hf);
	std::chrono::milliseconds mhf(hf);
	heightMeasure[0] = mhf;
	std::chrono::milliseconds mhs(hs);
	heightMeasure[1] = mhs;

	std::chrono::milliseconds msf(sf);
	sortingSwitch[0] = msf;
	std::chrono::milliseconds mss(ss);
	sortingSwitch[1] = mss;

	std::chrono::milliseconds mos(os);
	outlet[0] = mos;
	std::chrono::milliseconds mof(of);
	outlet[1] = mof;

	std::chrono::milliseconds movf(ovf);
	overall[0] = movf;
	std::chrono::milliseconds movs(ovs);
	overall[1] = movs;

	slowToFastFactor = (double)overall[0].count() / (double)overall[1].count();
	fastToSlowFactor = (double)overall[1].count() / (double)overall[0].count();
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
		case IN_SWITCH: 		return inSwitch[slowOrFast].count();
	}

}

double Calibration::getFastToSlow(void){
	return fastToSlowFactor;
}

double Calibration::getSlowToFast(void){
	return slowToFastFactor;
}


bool Calibration::pollLB(sensor_t sensor){
	return((in8(PORTB_ADDR) & sensor) == 0);
}


void Calibration::print(){
	for(int i = 0; i < 2; i++){
		std::cout << "Height: " << heightMeasure[i].count() << " Sort: " << sortingSwitch[i].count() << " Out: " << outlet[i].count() << " In: " << inlet[i].count() << " Overall" << overall[i].count() << "\n";
		std::cout << "Slow to Fast: " << slowToFastFactor << "Fast to Slow " << fastToSlowFactor << "\n";
	}
}



Calibration::Calibration(){}
Calibration::~Calibration(){}
