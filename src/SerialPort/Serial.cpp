//
// Created by Silt on 26.05.2017.
//

#include "Serial.h"
#include "Logger.h"
#include "LogScope.h"
#include "TopLevelProto/ITopLvlProtocoll.h"
#include <thread>
#include <Timer/TimerService.h>
#include <TopLevelProto/ITopLvlProtocoll.h>

Serial::Serial(SerialReceiver& rec, SerialSender& sender, SerialProtocoll& proto,const int channel_in,const int channel_out) :
    rec(rec),
    sender(sender),
    proto(proto),
	chid(channel_in),
	ch_in(channel_in),
    ch_out(channel_out)
{
	LOG_SCOPE
}

void Serial::operator()() {
	LOG_SCOPE
	running = true;
    //std::thread rec_thread(rec, chid);
    TimerService polRecTimer(chid, SERIAL_TIMEOUT_SIG); //Ping of life timer for receiving pol, set after first received msg (makes setup simple)
    TimerService polSendTimer(chid, SERIAL_SEND_POL);  //Ping of life timer for sending pols
    polSendTimer.setAlarm(2000, 0);
    while(running){
        uint8_t code;
        uint32_t  value;
        rcv::msg_t msg;
        serialized ser;
        LOG_DEBUG << "Serial Waiting for pulse \n";
        msg = ch_in.receivePulseMessage();
        LOG_DEBUG << "Serial received Pulse \n";
        code = msg.code;
        value = msg.value;
        pulse pm;
        switch(code){
            case SERIAL_TIMEOUT_SIG:
                LOG_ERROR << "Ping of life was not received \n";
                //TODO Serial Error handling, send error to main
                ch_out.sendPulseMessage(SER_OUT, POL);
                break;
            case SERIAL_SEND_POL:
            	LOG_DEBUG << "Serial received send pol \n";
                ser =  proto.wrapInFrame(SER_OUT, POL);
                sender.send((char *) ser.obj, ser.size);
                polSendTimer.setAlarm(2000, 0);
                break;
            case SER_REC_IN: //Msg from serial receiver
            	pm = proto.convToPulse((void *) value);
                if(pm.value != POL){ //POL doesnt need to be send to the main
                    ch_out.sendPulseMessage(pm.code, pm.value);
                }
                polRecTimer.stopAlarm();
                polRecTimer.setAlarm(SERIAL_POL_TIMEOUT, 0);
                break;
            case SER_REC_FAIL:
                LOG_ERROR << "Serial Recorder could'nt read msg from ser \n";
                //TODO Send Serial error msg
            case SER_OUT:
                ser =  proto.wrapInFrame(SER_OUT, value);
                sender.send((char *) ser.obj, ser.size);
                break;
            case TRANSM_OUT:
                ser =  proto.wrapInFrame(TRANSM_OUT, value);
                sender.send((char *) ser.obj, ser.size);
            default:
                LOG_ERROR<< "Serial received unknown cmd: " << code << "\n";
                //TODO Serial Error handling, send error to main
        }
    }
    //rec_thread.join();
    rec.kill();
}

void Serial::kill() {
    running = false;
}
