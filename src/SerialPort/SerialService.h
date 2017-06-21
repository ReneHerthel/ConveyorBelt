/*
 * SerialService.h
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#ifndef SERIALSERVICE_H_
#define SERIALSERVICE_H_

#include "Serial.h"
#include "SerialProtocoll.h"
#include "PulseMessageSenderService.h"

using namespace Serial_n;

class SerialService {
public:
	/**
	 * @param chid the channel the service should use to communicate with the serial
	 */
	SerialService(int chid);
	~SerialService();

	/**
	 * Send an object over the serial
	 * NOTE: Broken, its hard coded
	 */
	void sendObj(void* obj);


	/**
	 * Send an message over the serial
	 */
	void sendMsg(ser_proto_msg msg);

private:
	PulseMessageSenderService pms;
};

#endif /* SERIALSERVICE_H_ */
