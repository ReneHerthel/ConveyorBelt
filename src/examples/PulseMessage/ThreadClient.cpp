/*
 * ThreadClient.cpp
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */

#include "ThreadClient.h"

ThreadClient::ThreadClient(int chid) {
	// TODO Auto-generated constructor stub
	client_t = std::thread(&ThreadClient::task,this, chid);
}

ThreadClient::~ThreadClient() {
	// TODO Auto-generated destructor stub
}

void ThreadClient::task(int chid) {
	int coid = ConnectAttach_r(ND_LOCAL_NODE,0,chid,0,0);
	if(coid < 0) {
		// TODO error handling
		std::cout << "client connectAttach failed" << std::endl;
	}

	struct _pulse pulse;

	int err = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
	if(err) {
			// TODO error handling
			std::cout << "client MsgReceive_r failed" << std::endl;
	}



	std::cout << "Message received: " << pulse.value.sival_int << std::endl;

}

