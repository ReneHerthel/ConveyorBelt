// =====================================================================================
// LightSystemHAL.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMHAL_H
#define LIGHTSYSTEMHAL_H

#include "enum.h"
#include <iostream>

namespace HAL {
    class LightSystemHAL {
        public:
            void lightOn(Color color);
            void lightOff(Color color);
        private:
            void stub(Color color);
    };
}

#endif
