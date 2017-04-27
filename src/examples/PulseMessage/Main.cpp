/*
 * Main.cpp
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */
#include <sys/neutrino.h>
#include "ThreadClient.h"
#include "ThreadServer.h"
#include <chrono>

static void testThread(int i){
	std::cout << "Hier ist der Test Thread" << i << std::endl;
}

int main(void){
	std::cout << "Geht los hier" << std::endl;
	std::thread test_t(testThread, 100);

	std::cout << "Create Channel" << std::endl;
	int chid = ChannelCreate_r(0);
	if(chid < 0){
		std::cout << "Channel Create failed" << std::endl;
	}

	std::cout << "Channel Created" << std::endl;

	ThreadClient* client = new ThreadClient(chid);
	std::cout << "Client Created" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	ThreadServer* server = new ThreadServer(chid);
	std::cout << "Server Created" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Zuende hier" << std::endl;
}




