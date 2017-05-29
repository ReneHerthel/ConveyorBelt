//
// Created by Silt on 26.05.2017.
//

#include "Serial.h"
#include "../Logger/Logger.h"
#include "TopLevelProto/ITopLvlProtocoll.h"
#include <thread>

Serial::Serial(SerialReceiver &rec, SerialSender &sender,ITopLvlProtocoll &proto, int channel_in, int channel_out) :
    rec(rec),
    sender(sender),
    proto(proto)
{
    ch_in = new PulseMessageReceiverService(channel_in);
    ch_out = new PulseMessageSenderService(channel_out);
    std::thread receiver(rec, channel_in);

}

void Serial::run() {

    while(1){ //TODO make killable
        uint8_t code; //TODO wait for Wrapper fix
        uint32_t  value;
        pulse pm;
        serialized ser;
        ch_in->receivePulseMessage();
        switch(code){
            case SER_IN: ///TRANS_IN is also SER_IN here, becouse the SerialReceiver doesnt know
                pm = proto.convToPulse((void *) value);
                ch_out->sendPulseMessage(pm.value);
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
    }
}
