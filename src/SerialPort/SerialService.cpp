/*
 * SerialService.cpp
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#include "SerialService.h"

using namespace Serial_n;

SerialService::SerialService(int chid):
	pms(chid)
{}

SerialService::~SerialService() {}


void SerialService::sendObj(void* obj){
	pms.sendPulseMessage(TRANSM_OUT, (int)obj);
}


void SerialService::sendMsg(ser_proto_msg msg){
	pms.sendPulseMessage(SER_OUT, msg);
}
