// =====================================================================================
// LightSystemHAL.cpp : Provide methods to hide hardware dependend implementation
// 
//    Copyright (c) 2017 Stephan Jaenecke <stephan.jaenecke@haw-hamburg.de>
//						 Matthis Keppner <matthis.keppner@haw-hamburg.de>
// =====================================================================================

#include "LightSystemHal.h"

namespace HAL {
    void LightSystemHal::lightOn(Color color) {
        unsigned char bitMask;
        bitMask = 0;
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
           bitMask = 0;
           // nothing will happen
        }
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

    	unsigned char port_value = in8(PORTA_ADDR);
    	out8(PORTA_ADDR, (port_value | (1 << bitMask)));

    }

    void LightSystemHal::lightOff(Color color) {
    	unsigned char bitMask;
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
		   bitMask = 0;
		   // nothing will happen
		}
    	out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);

    	unsigned char port_value = in8(PORTA_ADDR);
    	out8(PORTA_ADDR, (port_value & ~(1 << bitMask)));
    }

}
