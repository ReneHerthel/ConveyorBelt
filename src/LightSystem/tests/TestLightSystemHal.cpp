#include <cstdlib>
#include <iostream>
#include "TestLightSystemHal.h"


void task(){
	LightSystemHAL hal9000;
	for(int i = 0;i<10;i++){
		hal9000.lightOn(RED);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		hal9000.lightOn(YELLOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		hal9000.lightOn(GREEN);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		hal9000.lightOff(RED);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		hal9000.lightOff(YELLOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		hal9000.lightOff(GREEN);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}

int main(int argc, char *argv[]){

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}

	using std;

	cout << "Starting Thread task!" << std::endl;
	thread thd(task);
	task.join();
	cout << "111!!!--->>>Finished<<<---!!!111" << std::endl;

}
