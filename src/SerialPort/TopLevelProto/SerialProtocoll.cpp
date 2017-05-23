/*
 * SerialTopLvlProtocoll.cpp
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#include "SerialProtocoll.h"

/**
 * This is an unidirectional Protocoll over Serial
 * One must always be the Sender of Pucks
 * One must always be the receiver Pucks
 * @param mode Be receiver or sender?
 */
SerialProtocoll::SerialProtocoll(Serial_mode mode) {

}

SerialProtocoll::~SerialProtocoll() {
	// TODO Auto-generated destructor stub
}

/**
 * Convert an array of bytes to an Code and Value for a pulse message
 * @param buff The arrray of bytes
 * @param size the amount of bytes to read from buff
 * @return struct with code and value
 */
pulse SerialProtocoll::convToPulse(char *buff, uint32_t size) {

}

/**
 * Wrap an array of bytes into a sendable frame
 * @param buff
 * @param size
 * @return
 */
serialized SerialProtocoll::wrapInFrame(char *buff, uint32_t size) {
    //TODO Check if implementation is usefull
    //TODO Needs to return the size, too
}

serialized SerialProtocoll::wrapInFrame(int8_t int8, int32_t int32) {

}


