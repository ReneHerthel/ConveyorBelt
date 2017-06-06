/**
 *       @file  LightSystemStubHal.h
 *      @brief  Provide stub class for hardware abstraction layer
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/07/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef LIGHTSYSTEMSTUBHAL_H_
#define LIGHTSYSTEMSTUBHAL_H_

#include "BLightSystem.h"
#include "LightSystemEnum.h"
#include "Logger.h"
#include <iostream>

namespace HAL {
    class LightSystemStubHal: public BLightSystem {
        public:
            void lightOn(Color color);
            void lightOff(Color color);
    };
}

#endif /* LIGHTSYSTEMSTUBHAL_H_ */

