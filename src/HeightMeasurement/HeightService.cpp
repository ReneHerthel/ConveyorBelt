/*
 * HeightService.cpp
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#include "HeightService.h"
#include "HeightSignal.h"

HeightService::HeightService(int chid):
	pms(chid)
{}

void HeightService::startMeasuring() {
	pms.sendPulseMessage(0, HeightMeasurement::START);
}

void HeightService::stopMeasuring() {
	pms.sendPulseMessage(0, HeightMeasurement::STOP);
}

