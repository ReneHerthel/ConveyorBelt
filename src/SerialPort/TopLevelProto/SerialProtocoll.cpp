/*
 * SerialTopLvlProtocoll.cpp
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#include "SerialProtocoll.h"
#include "ITopLvlProtocoll.h"

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

pulse SerialProtocoll::convToPulse(char *buff, uint32_t size) {

}


serialized SerialProtocoll::wrapInFrame(char *buff, uint32_t size) {
    //TODO Check if implementation is usefull
    //TODO Needs to return the size, too
}


//TODO Untested
serialized SerialProtocoll::wrapInFrame(int8_t code, int32_t value) {
    serialized resu;
    int32_t* msg = new int32_t;
    switch(code){
        case IN: //Inout nothing needs to be done
        case OUT :
            *msg = value;
            resu.size = sizeof(int32_t);
            resu.obj = msg;
            break;
        case TRANSM_IN:
        case TRANSM_OUT:
            ISerializable* obj = (ISerializable*) value;
            resu = obj->serialize();
            break;
        default: //TODO error handler
            break;
    }

    return resu;
}


