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
#include <string.h>
#include <Logger.h>
#include <Logscope.h>

/**
 * This is an unidirectional Protocoll over Serial
 * One must always be the Sender of Pucks
 * One must always be the receiver Pucks
 * @param mode Be receiver or sender?
 */
SerialProtocoll::SerialProtocoll(Serial_mode mode) {
    // TODO mode is not implemented
}

SerialProtocoll::~SerialProtocoll() {
	// TODO Auto-generated destructor stub
}

pulse SerialProtocoll::convToPulse(void *buff) {
	LOG_SCOPE;
    pulse resu;
    msg msg_in = *(msg*)buff;
    resu.code = SER_IN;
    switch(msg_in){
        case ACCEPT:
        case STOP:
        case RESUME:
        case INVALID:
        case RECEIVED:
        case POL:
            resu.value = msg_in;
            break;
        case TRANSM:
            {
                ISerializable *obj = new SerialTestStub;
                obj->deserialize(((char*)buff) + sizeof(msg)); //cast to char* because void* cant be used in arith
                resu.value = (uint32_t) obj;
            }
            break;
        default:
            break; //TODO ERROR
    }
    return resu;
}


serialized SerialProtocoll::wrapInFrame(int8_t code, int32_t value) {
	LOG_SCOPE;
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
                memcpy((frame+sizeof(msg)), tmp.obj, tmp.size);
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



