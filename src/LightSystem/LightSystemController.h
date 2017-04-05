// =====================================================================================
// LightSystemController.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMCONTROLLER_H
#define LIGHTSYSTEMCONTROLLER_H

class LightSystemController : public ILightSystem {
    public:
        LightSystemController(LightSystemService* serviceId);
        void setWarningLevel(Level warningLevel);
        int main(void);
    private:
        Thread* threadId;
        LightSystemService* serviceId;
}

#endif
