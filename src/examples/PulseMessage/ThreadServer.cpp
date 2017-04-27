/*
 * ThreadServer.cpp
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */

#include "ThreadServer.h"

ThreadServer::ThreadServer(int chid) {
	// TODO Auto-generated constructor stub
	server_t = std::thread(&ThreadServer::task,this, chid);

}

ThreadServer::~ThreadServer() {
	// TODO Auto-generated destructor stub
}

void ThreadServer::task(int chid) {
		int coid = ConnectAttach_r(ND_LOCAL_NODE,0,chid,0,0);
		if(coid < 0) {
			// TODO error handling
			std::cout << "client connectAttach failed" << std::endl;
		}

		int err = MsgSendPulse_r(coid, sched_get_priority_min(0),0,333999);
		if(err) {
			// TODO error handling
			std::cout << "client MsgReceive_r failed" << std::endl;
		}

		std::cout << "Server finished" << std::endl;
}

