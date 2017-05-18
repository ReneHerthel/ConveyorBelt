/**
 *       @file  BLightSystem.h
 *      @brief  Hardware abstraction for lights
 *
 *     @author  Matthis Keppner
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  04/05/2017
 *   Copyright  Copyright (c) 2017 Matthis Keppner
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef BLIGHTSYSTEM_H_
#define BLIGHTSYSTEM_H_

#include "LightSystemEnum.h"

namespace HAL {
    class BLightSystem {
        public:
    		virtual ~BLightSystem() {};
            /**
             * @brief   Turn light on
             * @param   [in] color Specify by color which light to manipulate
             */
            virtual void lightOn(Color color) = 0;
            /**
             * @brief   Turn light off
             * @param   [in] color Specify by color which light to manipulate
             */
            virtual void lightOff(Color color) = 0;
    };
}


#endif /* BLIGHTSYSTEM_H_ */
