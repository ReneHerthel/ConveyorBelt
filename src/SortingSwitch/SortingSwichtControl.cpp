/*
 * SortingSwichtControl.cpp
 *
 *  Created on: 15.06.2017
 *      Author: aca619
 */

#include "SortingSwichtControl.h"
#include "DistanceTracker.h"
#include "SortingSwitchService.h"
#include "PulseMessageReceiverService.h"
#include "DistanceEnum.h"
#include "Logger.h"

SortingSwichtControl::SortingSwichtControl(int chid):
	distTracker(chid, SSC_CLOSE)
	, ssService()
{
	LOG_DEBUG << "Started Dist tracker with chid" << chid << "\n";
}

SortingSwichtControl::~SortingSwichtControl() {
}

void SortingSwichtControl::open(void){
	ssService.sortingSwitchOpen();
	distTracker.startAlarm(0, DistanceSpeed::IN_SWITCH, 1); //Value doesnt matter, IN_SWITCH, no delta (100%)
}

void SortingSwichtControl::close(void){
	ssService.sortingSwitchClose();
}

