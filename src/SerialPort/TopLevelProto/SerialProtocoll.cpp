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
#include "PuckSignal.h"


using namespace Serial_n;

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
    pulse resu;
    ser_proto_msg msg_in = *(ser_proto_msg*)buff;
    resu.code = SER_IN;
    switch(msg_in){
        case ACCEPT_SER:
        case STOP_SER:
        case RESUME_SER:
        case INVALID_SER:
        case RECEIVED_SER:
        case SLIDE_FULL_SER:
        case POL_SER:
        case ERROR_SER:
        case ESTOP_SER:
        case SLIDE_EMTPY_SER:
            resu.value = msg_in;
            break;
        case TRANSM_SER:
            {
            	resu.code = TRANSM_IN;
                ISerializable *obj = new PuckSignal::PuckType;
                obj->deserialize(((char*)buff) + sizeof(ser_proto_msg)); //cast to char* because void* cant be used in arith
                resu.value = (uint32_t) obj;
            }
            break;
        default:
        	LOG_WARNING << "[SerialProtocoll] convToPulse() Got an undefined messages: " << (int)msg_in << endl;
            break; //TODO ERROR
    }
    return resu;
}


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
                char* frame = new char[tmp.size+ sizeof(ser_proto_msg)]; //make space for msg type
                memcpy((frame+sizeof(ser_proto_msg)), tmp.obj, tmp.size);
                ser_proto_msg *msg_ptr = (ser_proto_msg *) frame;
                *msg_ptr = TRANSM_SER;
                resu.obj = frame;
                resu.size = tmp.size + sizeof(ser_proto_msg);
                break;
            }
        default: //TODO error handler
        	LOG_WARNING << "[SerialProtocoll] Trying to wrap unknown code: " << (int)code << endl;
            break;
    }

    return resu;
}

pulse SerialProtocoll::protocollState(int8_t int8, int32_t int32) {
    pulse empty; //TODO Fill with logic
    return  empty;
}



