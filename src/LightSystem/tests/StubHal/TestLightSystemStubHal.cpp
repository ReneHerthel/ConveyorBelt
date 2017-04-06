/*
 * TestLightSystemStubHal.cpp : 
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include "TestLightSystemStubHal.h"

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
    cout << __FUNCTION__ << ": Hardware priviledge request stub!" << endl;

	thread thd(task);
	thd.join();
}
