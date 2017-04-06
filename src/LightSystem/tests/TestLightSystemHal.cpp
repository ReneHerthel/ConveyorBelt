/*
 * TestLightSystemStubHal.cpp : 
 * 
 * Copyright (c) 2017 Matthis Keppner <matthis.keppner@haw-hamburg.de>
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include "TestLightSystemHal.h"

using namespace HAL;
using namespace std;

void task() {
	LightSystemStubHal hal;
    cout << __FUNCTION__ << ": Thread started!" << endl;

	for (int i = 0; i<10; i++) {
		hal.lightOn(RED);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		hal.lightOn(YELLOW);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		hal.lightOn(GREEN);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		hal.lightOff(RED);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		hal.lightOff(YELLOW);
		this_thread::sleep_for(std::chrono::milliseconds(100));
		hal.lightOff(GREEN);
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	cout << __FUNCTION__<< ": Thread finished!" << std::endl;
}

int main(int argc, char *argv[]) {
    
    // Request priviledges for the current thread to access hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}

	thread thd(task);
	task.join();
}
