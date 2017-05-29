//
// Created by Silt on 26.05.2017.
//

#include "Serial.h"
#include "Logger.h"
#include "LogScope.h"
#include "TopLevelProto/ITopLvlProtocoll.h"
#include <thread>

Serial::Serial(SerialReceiver &rec, SerialSender &sender,ITopLvlProtocoll &proto, int channel_in, int channel_out) :
    rec(rec),
    sender(sender),
    proto(proto)
{
	LOG_SCOPE
    ch_in = new PulseMessageReceiverService(channel_in);
    ch_out = new PulseMessageSenderService(channel_out);
    rec_thread(std::ref(rec));
}

void Serial::operator()() {
	LOG_SCOPE
    while(1){ //TODO make killable
        uint8_t code; //TODO wait for Wrapper fix
        uint32_t  value;
        IPulseMessageReceiver::rcv_msg_t msg;
        serialized ser;
        LOG_DEBUG << "Serial Waiting for pulse \n";
        msg = ch_in->receivePulseMessage();
        LOG_DEBUG << "Serial received Pulse \n";
        code = msg.code;
        value = msg.value;
        pulse pm;
        switch(code){
            case SER_IN: ///TRANS_IN is also SER_IN here, because the SerialReceiver doesnt know
            	pm = proto.convToPulse((void *) value);
                ch_out->sendPulseMessage(pm.code, pm.value);
                break;
                break;
            case SER_OUT:
                ser =  proto.wrapInFrame(SER_OUT, value);
                sender.send((char *) ser.obj, ser.size);
                break;
            case TRANSM_OUT:
                
            default:
                LOG_ERROR<< "Serial received unknown cmd: " << code << "\n";
                //TODO Serial Error handling
        }
        break;
    }
}
