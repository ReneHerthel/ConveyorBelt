/*
 * Main.cpp
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */
#include <iostream>
#include <sys/neutrino.h>
#include "ITimer.h"
#include "TimerService.h"

#define PM_CODE 4
#define PM_VALUE 123456

static void testThread(int i){
	std::cout << "Hier ist der Test Thread" << i << std::endl;
}

int main(void){
	std::cout << "Geht los hier" << std::endl;

	int chid = ChannelCreate_r(0);
	if(chid < 0){
		std::cout << "Channel Create failed" << std::endl;
	}

	struct _pulse pulse;

	ITimer* timer  = new TimerService(chid, PM_CODE, PM_VALUE);
	timer->setAlarm(9999);


	int err = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
		if(err) {
				// TODO error handling
				std::cout << "client MsgReceive_r failed" << std::endl;
		}
	std::cout << "Message received: " << pulse.value.sival_int << std::endl;

	std::cout << "Zuende hier" << std::endl;
}




