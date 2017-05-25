/*
 * SerialTopLvlProtocoll.cpp
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#include <cstring>
#include "SerialProtocoll.h"
#include "ITopLvlProtocoll.h"
#include "../../Tests/Serial/SerialTestStub.h"

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

//TODO Refactor, size isnt needed
pulse SerialProtocoll::convToPulse(char *buff, uint32_t size) {
    pulse resu;
    msg msg_in = *(msg*)buff;
    resu.code = SER_IN;
    switch(msg_in){
        case ACCEPT:
        case STOP:
        case RESUME:
        case INVALID:
            resu.value = msg_in;
            break;
        case TRANSM:
            {
                ISerializable *obj = new SerialTestStub;
                obj->deserialize(buff + sizeof(msg));
                resu.value = (uint32_t) obj;
            }
            break;
        default:
            break; //TODO ERROR
    }
    return resu;
}


serialized SerialProtocoll::wrapInFrame(char *buff, uint32_t size) {
    //TODO Check if implementation is usefull
    //TODO Needs to return the size, too
}


//TODO Untested
serialized SerialProtocoll::wrapInFrame(int8_t code, int32_t value) {
    serialized resu;
    switch(code){
        case SER_IN: //Inout nothing needs to be done
        case SER_OUT :
            {
                int32_t* msg_type = new int32_t;
                *msg_type = value;
                resu.size = sizeof(int32_t);
                resu.obj = msg_type;
                break;
            }
        case TRANSM_IN:
        case TRANSM_OUT:
            {
                serialized tmp;
                ISerializable* obj = (ISerializable*) value;
                tmp = obj->serialize();
                char* frame = new char[tmp.size+ sizeof(msg)]; //make space for msg type
                memcpy(frame+sizeof(msg), tmp.obj, tmp.size+4);
                msg *msg_ptr = (msg *) frame;
                *msg_ptr = TRANSM;
                resu.obj = frame;
                break;
            }
        default: //TODO error handler
            break;
    }

    return resu;
}

pulse SerialProtocoll::protocollState(int8_t int8, int32_t int32) {
    pulse empty; //TODO Fill with logic
    return  empty;
}



