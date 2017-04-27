/*
 * ThreadServer.h
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */

#ifndef THREADSERVER_H_
#define THREADSERVER_H_

#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <thread>
#include <iostream>
#include <sys/netmgr.h>

class ThreadServer {
public:
	ThreadServer(int chid);
	virtual ~ThreadServer();
private:
	void task(int chid);
	std::thread server_t;

};

#endif /* THREADSERVER_H_ */
