// =====================================================================================
// LightSystemStubHal.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMSTUBHAL_H_
#define LIGHTSYSTEMSTUBHAL_H_

#include "BLightSystem.h"
#include "enum.h"
#include <iostream>

namespace HAL {
    class LightSystemStubHal: public BLightSystem {
        public:
            void lightOn(Color color);
            void lightOff(Color color);
    };
}

#endif /* LIGHTSYSTEMSTUBHAL_H_ */

