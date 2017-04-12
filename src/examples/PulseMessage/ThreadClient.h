/*
 * ThreadClient.h
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */

#ifndef THREADCLIENT_H_
#define THREADCLIENT_H_

#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <thread>
#include <iostream>
#include <sys/netmgr.h>

class ThreadClient {
public:
	ThreadClient(int chid);
	virtual ~ThreadClient();
private:
	void task(int chid);
	std::thread client_t;
};

#endif /* THREADCLIENT_H_ */
