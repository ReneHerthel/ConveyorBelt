/**
 *       @file  LightSystemStubHal.cpp
 *      @brief  Implement stubs
 *
 * Interface methods of BLightSystem will print parameter color to log.
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/07/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#include "LightSystemStubHal.h"

using namespace std;

namespace HAL {
    /* TODO: Define log level message */
    void LightSystemStubHal::lightOn(Color color) {
     //   LOG_DEBUG << __FUNCTION__ << ": " << color << endl;
    }
    void LightSystemStubHal::lightOff(Color color) {
       // LOG_DEBUG << __FUNCTION__ << ": " << color << endl;
    }
}
