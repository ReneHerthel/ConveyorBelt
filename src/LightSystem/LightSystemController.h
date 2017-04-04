// =====================================================================================
// LightSystemController.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

class LightSystemController : public ILightSystem {
    public:
        LightSystemController(LightSystemService* serviceId);
        void setWarningLevel(Level warningLevel);
        int main(void);
    private:
        Thread* threadId;
        Timer* timerId;
        LightSystemService* serviceId;
}
