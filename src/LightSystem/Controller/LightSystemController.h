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
#include "BLightSystem.h"
#include "enum.h"
#include "LightSystemService.h"

using namespace std;
using namespace HAL;

class LightSystemController {
    public:
		LightSystemController(int chid
				, BLightSystem* boundary);
		bool isRunning;

    private:
		int chid;
        BLightSystem* boundary;
        int task(void);
        int control(void);
        Frequency frequency;
        Color color;
        thread controlThread;
        thread taskThread;
};

#endif
