// =====================================================================================
// LightSystemController.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMCONTROLLER_H
#define LIGHTSYSTEMCONTROLLER_H

class LightSystemController {
    public:
        LightSystemController(LightSystemService* serviceId);
        int main(void);
        void setLights(Color lightColor, Frequency lightFrequency);

    private:
        Thread* threadId;
        LightSystemService* serviceId;
        Timer* timerId;
        LightSystemHAL halObject;
};

#endif
