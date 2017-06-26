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
		PortA::getInstance().bitClear(ALL_MASK);
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
		        LOG_DEBUG << "lightOff: Clear bitmask: GREEN" << endl;
				bitMask = GREEN_MASK;
				break;
			case YELLOW:
		        LOG_DEBUG << "lightOff: Clear bitmask: YELLOW" << endl;
				bitMask = YELLOW_MASK;
				break;
			case RED:
		        LOG_DEBUG << "lightOff: Clear bitmask: RED" << endl;
				bitMask = RED_MASK;
				break;
			case ALL_COLORS:
		        LOG_DEBUG << "lightOff: Clear bitmask: ALL" << endl;
				bitMask = ALL_MASK;
				break;
			default:
				/* Invalid value, do nothing */
				;
        }

    	/* Clear all before setting */
    	PortA::getInstance().bitClear(ALL_MASK);
        /* Set requested bit */
        PortA::getInstance().bitSet(bitMask);
    }

    void LightSystemHal::lightOff(Color color) {
        LOG_SCOPE;
    	unsigned char bitMask = 0;

        /* Prepare bitmask according to color */
    	switch (color) {
			case GREEN:
		        LOG_DEBUG << "lightOff: Clear bitmask: GREEN" << endl;
				bitMask = GREEN_MASK;
				break;
			case YELLOW:
		        LOG_DEBUG << "lightOff: Clear bitmask: YELLOW" << endl;
				bitMask = YELLOW_MASK;
				break;
			case RED:
		        LOG_DEBUG << "lightOff: Clear bitmask: RED" << endl;
				bitMask = RED_MASK;
				break;
			case ALL_COLORS:
		        LOG_DEBUG << "lightOff: Clear bitmask: ALL" << endl;
				bitMask = ALL_MASK;
				break;
			default:
				/* Invalid value, do nothing */
				;
		}

        /* Clear requested bit */
        PortA::getInstance().bitClear(bitMask);
    }

    bool LightSystemHal::checkIfPreviouslySetTo(Color newColor) {
    	return(lastColor == newColor);
    }
}
