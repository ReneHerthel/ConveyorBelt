/**
 *       @file  LightSystemHal.cpp
 *      @brief  Provide methods to hide hardware dependend implementation
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *     @author  Matthis Keppner <matthis.keppner@haw-hamburg.de>
 *   @internal
 *     Created  05/06/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 *   Copyright  Copyright (c) 2017 Matthis Keppner
 */

#include "LightSystemHal.h"

namespace HAL {
    /* TODO: Merge methods lightOn and lightOff to reduce code duplication */
    void LightSystemHal::lightOn(Color color) {
        LOG_SCOPE;
        unsigned char bitMask = 0;
        
        /* Prepare bitmask according to color */
    	switch (color) {
        case GREEN:
        	bitMask = GREEN_SHIFT;
        	break;
        case YELLOW:
        	bitMask = YELLOW_SHIFT;
        	break;
        case RED:
        	bitMask = RED_SHIFT;
        	break;
        case ALL:
        	bitMask = ALL_SHIFT;
        	break;
        default:
           /* Invalid value, do nothing */
        }
        /* TODO: What is this for? */
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

        /* Save old port value */
    	unsigned char port_value = in8(PORTA_ADDR);
        /* Set requested bit */
        LOG_DEBUG << "Write to port " << PORTA_ADDR << " Value: " << port_value << " Set bitmask: " << bitMask;
    	out8(PORTA_ADDR, (port_value | (1 << bitMask)));
    }

    void LightSystemHal::lightOff(Color color) {
        LOG_SCOPE;
    	unsigned char bitMask = 0;

        /* Prepare bitmask according to color */
    	switch (color) {
        case GREEN:
        	bitMask = GREEN_SHIFT;
			break;
		case YELLOW:
			bitMask = YELLOW_SHIFT;
			break;
		case RED:
			bitMask = RED_SHIFT;
			break;
		case ALL:
			bitMask = ALL_SHIFT;
			break;
		default:
           /* Invalid value, do nothing */
		}
        /* TODO: What is this for? */
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

        /* Save old port value */
    	unsigned char port_value = in8(PORTA_ADDR);
        /* Clear requested bit */
        LOG_DEBUG << "Write to port " << PORTA_ADDR << " Value: " << port_value << " Clear bitmask: " << bitMask;
    	out8(PORTA_ADDR, (port_value & ~(1 << bitMask)));
    }

}
