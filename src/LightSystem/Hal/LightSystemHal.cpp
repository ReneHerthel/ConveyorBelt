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
	LightSystemHal::LightSystemHal()
	: lastColor(ALL_COLORS) {};

	LightSystemHal::~LightSystemHal() {
		out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);
		PortA::getInstance().bitClear(ALL_SHIFT);
	}

    /* TODO: Merge methods lightOn and lightOff to reduce code duplication */
    void LightSystemHal::lightOn(Color color) {
        LOG_SCOPE;
        /* Remember last color */
        lastColor = color;

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
			case ALL_COLORS:
				bitMask = ALL_SHIFT;
				break;
			default:
				/* Invalid value, do nothing */
				;
        }
        /* FIXME: Move to PortA singleton */
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

        /* Set requested bit */
        LOG_DEBUG << "lightOn: Set bitmask: " << bitMask << endl;
        PortA::getInstance().bitSet(1 << bitMask);
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
			case ALL_COLORS:
				bitMask = ALL_SHIFT;
				break;
			default:
				/* Invalid value, do nothing */
				;
		}
        /* TODO: What is this for? */
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

        /* Clear requested bit */
        LOG_DEBUG << "lightOff: Clear bitmask: " << bitMask << endl;
        PortA::getInstance().bitClear(1 << bitMask);
    }

    bool LightSystemHal::checkIfPreviouslySetTo(Color newColor) {
    	LOG_SCOPE;
    	return(lastColor == newColor);
    }
}
