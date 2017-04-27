// =====================================================================================
// LightSystemController.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMCONTROLLER_H
#define LIGHTSYSTEMCONTROLLER_H

#include <iostream>
#include <thread>
#include <vector>
#include <sys/neutrino.h>
#include "ITimer.h"
#include "BLightSystem.h"
#include "enum.h"

using namespace std;
using namespace HAL;

class LightSystemController {
    public:
		LightSystemController(int chid
				, ITimer* timer
				, BLightSystem* boundary);
		bool isRunning;

    private:
		int chid;
        ITimer* timer;
        BLightSystem* boundary;
        int task(void);
};



#endif
