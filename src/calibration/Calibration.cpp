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
#include "HeightMeasurementController.h"
#include "HeightMeasurementHal.h"
#include "PulseMessageReceiverService.h"
#include <iostream>
#include <fstream>

using namespace chrono;

/**
 * Calibrate the light barrier distances
 */
void Calibration::calibrate(int mainChid){
	ConveyorBeltService cbs;
    SortingSwitchService sss;
    rcv::PulseMessageReceiverService pmr(mainChid);
    HeightMeasurementHal hal;
    uint16_t data = 0;
    uint32_t data_avg = 0;

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
			LOG_ERROR << "Can't get Hardware access, therefore can't do anything." << std::endl;
			return;
	}

	hal.read(data);
	hmCal.refHeight = data;

	LOG_DEBUG << "GOT HW ACCESS" << std::endl;

	cbs.changeState(ConveyorBeltState::STOP);


	//CENTER THE PUCK AND CALC TIME FOR RUNNING THROUGH A LB
	while(pmr.receivePulseMessage().value != interrupts::INLET_IN);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cbs.changeState(RIGHTFAST);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cbs.changeState(RIGHTSLOW);
	while(pmr.receivePulseMessage().value != interrupts::HEIGHTMEASUREMENT_IN);
	auto lb_in = system_clock::now();


	for(int i = 0; i < 100; i++){
		hal.read(data);
		data_avg += data;
	}
	data_avg /= 100;

	hmCal.surfaceHeight = (uint16_t)data_avg;

	while(pmr.receivePulseMessage().value != interrupts::HEIGHTMEASUREMENT_OUT);
	auto lb_out = system_clock::now();

	milliseconds lb_throughput = duration_cast<milliseconds>(lb_out - lb_in);

	cbs.changeState(LEFTFAST);
	while(pmr.receivePulseMessage().value != interrupts::INLET_IN);
	cbs.changeState(ConveyorBeltState::STOP);
	std::this_thread::sleep_for(std::chrono::milliseconds(250));

	for(int i = 0; i < 2; i++){
		break; //TODO REMOVE
		if(i == 0) 	cbs.changeState(RIGHTFAST);
		else		cbs.changeState(RIGHTSLOW);

		while(pmr.receivePulseMessage().value != interrupts::INLET_OUT);
		auto start = system_clock::now();

		auto last_lb = system_clock::now();

		while(pmr.receivePulseMessage().value != interrupts::HEIGHTMEASUREMENT_IN);
		heightMeasure[i] = milliseconds(duration_cast<milliseconds>(system_clock::now() - last_lb));
		sss.sortingSwitchOpen();
		while(pmr.receivePulseMessage().value != interrupts::HEIGHTMEASUREMENT_OUT);
		last_lb = system_clock::now();

		while(pmr.receivePulseMessage().value != interrupts::SWITCH_IN);
		sortingSwitch[i] = duration_cast<milliseconds>(system_clock::now()  - last_lb);
		while(pmr.receivePulseMessage().value != interrupts::SWITCH_OUT);
		last_lb = system_clock::now();

		while(pmr.receivePulseMessage().value != interrupts::OUTLET_IN);
		outlet[i] = duration_cast<milliseconds>(system_clock::now() - last_lb);
		overall[i] = duration_cast<milliseconds>(system_clock::now() - start);

		cbs.changeState(ConveyorBeltState::STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		cbs.changeState(LEFTFAST);
		while(pmr.receivePulseMessage().value != interrupts::HEIGHTMEASUREMENT_IN);
		sss.sortingSwitchClose();
		while(pmr.receivePulseMessage().value != interrupts::INLET_IN);
		cbs.changeState(ConveyorBeltState::STOP);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	sss.sortingSwitchClose(); //Safety
	while(pmr.receivePulseMessage().value != interrupts::INLET_OUT);
	inSwitch[0] = milliseconds((int)((double)outlet[0].count()/2.5)); //TODO make readable
	inSwitch[1] = milliseconds((int)((double)outlet[1].count()/2.5));

	slowToFastFactor = (double)overall[0].count() / (double)overall[1].count();
	fastToSlowFactor = (double)overall[1].count() / (double)overall[0].count();

	calibrateHeighMeasurement();
}


bool  Calibration::saveToDisk(std::string path){
	std::ofstream file(path);
	for(int i = 0; i < 2; i++){
		file << overall[i].count() << " " << heightMeasure[i].count() << " " << sortingSwitch[i].count()
			 << " " << outlet[i].count() << " " << inlet[i].count() << " " << inSwitch[i].count()
			 << " " << slowToFastFactor << " " << fastToSlowFactor << " ";
	}
	file << hmCal.delta << " " << hmCal.highHeight << " " << hmCal.holeHeight << " " << hmCal.invalidHeight << " " << hmCal.lowHeight << " " << hmCal.refHeight << " " << hmCal.surfaceHeight;
}

bool  Calibration::loadFromDisk(std::string path){
	std::ifstream file(path);
	uint32_t overall_in;
	uint32_t heightMeasure_in;
	uint32_t sortingSwitch_in;
	uint32_t outlet_in;
	uint32_t inlet_in;
	uint32_t inSwitch_in;
	double slowToFastFactor_in;
	double fastToSlowFactor_in;

	for(int i = 0; i < 2; i++){
		file >> overall_in >> heightMeasure_in >> sortingSwitch_in >> outlet_in >> inlet_in >> inSwitch_in
			 >> slowToFastFactor_in >> fastToSlowFactor_in;
		overall[i] 			= milliseconds(overall_in);
		heightMeasure[i] 	= milliseconds(heightMeasure_in);
		sortingSwitch[i] 	= milliseconds(sortingSwitch_in);
		outlet[i] 			= milliseconds(outlet_in);
		inlet[i] 			= milliseconds(inlet_in);
		inSwitch[i] 		= milliseconds(inSwitch_in);
		slowToFastFactor    = slowToFastFactor_in;
		fastToSlowFactor 	= fastToSlowFactor_in;
	}
	file >> hmCal.delta >> hmCal.highHeight >> hmCal.holeHeight >> hmCal.invalidHeight >> hmCal.lowHeight >> hmCal.refHeight >> hmCal.surfaceHeight;
}



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


	inlet[0] = std::chrono::milliseconds(INLET_CAL_FAST); //Measured ~1.8 seconds for, so half is a good gues
	inlet[1] = std::chrono::milliseconds(INLET_CAL_SLOW); //Measured ~1.8 seconds for slow

	slide[0] = std::chrono::milliseconds(SLIDE_TIMER_FAST);
	slide[1] = std::chrono::milliseconds(SLIDE_TIMER_SLOW);

	slowToFastFactor = (double)overall[0].count() / (double)overall[1].count();
	fastToSlowFactor = (double)overall[1].count() / (double)overall[0].count();

}

void  Calibration::calibrateHeighMeasurement(void){

	double puckHeight = hmCal.refHeight - hmCal.surfaceHeight; /*!< Height of Puck */
	puckHeight /= SURFACE;

	hmCal.holeHeight = hmCal.refHeight - ((uint16_t)(puckHeight * HOLE));
	hmCal.highHeight = hmCal.refHeight - ((uint16_t)(puckHeight * LOGICAL_1));
	hmCal.lowHeight = hmCal.refHeight - ((uint16_t)(puckHeight * LOGICAL_0));
	hmCal.invalidHeight = hmCal.refHeight - ((uint16_t)(puckHeight * INVALID));

	uint16_t delta;
	delta = (hmCal.invalidHeight - hmCal.lowHeight) / 2;

	hmCal.delta = delta;
}

HeightMeasurementController::CalibrationData Calibration::getHmCalibration(void){
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
		case SLIDE:				return slide[slowOrFast].count();
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
		std::cout << "Height: " << heightMeasure[i].count() << " Sort: " << sortingSwitch[i].count() << " Out: " << outlet[i].count() << " In: " << inlet[i].count() << " Overall " << overall[i].count() << "\n";
		std::cout << " Slow to Fast: " << slowToFastFactor << " Fast to Slow " << fastToSlowFactor << "\n";
	}
}



Calibration::Calibration(){}
Calibration::~Calibration(){}
