/*
 * BLightSystem.h
 *
 *  Created on: 05.04.2017
 *      Author: Matthis Keppner
 */

#ifndef BLIGHTSYSTEM_H_
#define BLIGHTSYSTEM_H_

#include "enum.h"

namespace HAL {
    class BLightSystem {
        public:
    		// This virtual function is virtual, really.
            virtual void lightOn(Color color) = 0;
            virtual void lightOff(Color color) = 0;
    };
}


#endif /* BLIGHTSYSTEM_H_ */
