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
            void lightOn(Color color);
            void lightOff(Color color);
    };
}


#endif /* BLIGHTSYSTEM_H_ */
