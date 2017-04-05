// =====================================================================================
// LightSystemController.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMCONTROLLER_H
#define LIGHTSYSTEMCONTROLLER_H

#include "ITimer.h"
#include "BLightSystem.h"

class LightSystemController {
    public:
		LightSystemController(int chid, ITimer* timer, BLightSystem* boundary);

    private:
		int chid;
        ITimer* timer;
        BLightSystem* halObject;
        int task(void);
        void setLights(Color lightColor, Frequency lightFrequency);

};

#endif
