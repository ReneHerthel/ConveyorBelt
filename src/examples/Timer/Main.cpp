/*
 * Main.cpp
 *
 *  Created on: 06.04.2017
 *      Author: aca619
 */
#include <iostream>
#include <chrono>
#include <sys/neutrino.h>
#include "ITimer.h"
#include "TimerService.h"

#define PM_CODE 4
#define PM_VALUE 123456

int main(void){
	std::cout << "Geht los hier" << std::endl;

	int chid = ChannelCreate_r(0);
	if(chid < 0){
		std::cout << "Channel Create failed" << std::endl;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;

	struct _pulse pulse;

	ITimer* timer  = new TimerService(chid, PM_CODE);

	start = std::chrono::system_clock::now();

	timer->setAlarm(500, PM_VALUE);

	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	timer->stopAlarm();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	timer->resumeAlarm();

	int err = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
		if(err) {
				// TODO error handling
				std::cout << "client MsgReceive_r failed" << std::endl;
		}
	end = std::chrono::system_clock::now();

	int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();

	std::cout << "Message received: " << pulse.value.sival_int << " after: " << elapsed_seconds << std::endl;

	std::cout << "Zuende hier" << std::endl;

	start = std::chrono::system_clock::now();

	timer->setAlarm(500, PM_VALUE);

	err = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
		if(err) {
				// TODO error handling
				std::cout << "client MsgReceive_r failed" << std::endl;
		}
	end = std::chrono::system_clock::now();

	elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();

	std::cout << "Message received: " << pulse.value.sival_int << " after: " << elapsed_seconds << std::endl;

	std::cout << "Zuende hier" << std::endl;
}




