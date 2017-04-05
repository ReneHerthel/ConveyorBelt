// =====================================================================================
// LightSystemController.cpp : Controller sets Lights according to
// warning level
// 
//    Copyright (c) 2017 Stephan Jaenecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemController.h"


LightSystemController :: LightSystemController(int chid, ITimer* timer, BLightSystem* boundary)
	: chid(chid)
	, timer(timer)
	, boundary(boundary)
{}

void LightSystemController::setLights(Color lightColor, Frequency lightFrequency) {
            if ( !lightFrequency ) {
                halObject.lightOn(lightColor);
            } else {
                // TODO: Start timer according to frequency
            }
}

int LightSystemController::task(){
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1)
	{
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}

}
