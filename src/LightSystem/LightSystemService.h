// =====================================================================================
// LightSystemService.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMSERVICE_H
#define LIGHTSYSTEMSERVICE_H

#include "enum.h"
#include "LightSystemHAL.h"

class LightSystemService {
    private:
        Timer* timerId;
        LightSystemHAL halObject;
    public:
        LightSystemService(LightSystemHAL halObject);
        void setLights(Color lightColor, Frequency lightFrequency);
}

#endif
