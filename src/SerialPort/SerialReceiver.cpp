//
// Created by Silt on 07.05.2017.
//

#include "Serial_def.h"
#include "SerialReceiver.h"
#include "../Logger/Logger.h"
#include "../Logger/LogScope.h"
#include "../Wrapper/PulseMessageSender/IPulseMessageSender.h"
#include "../Wrapper/PulseMessageSender/PulseMessageSenderService.h"

SerialReceiver::SerialReceiver(char *path) {
    in = open(path, O_RDWR | O_CREAT | O_BINARY);
}

SerialReceiver::~SerialReceiver() {
    close(in);
}

int SerialReceiver::fail() {
    return err;
}

char* SerialReceiver::receive() {
    LOG_SCOPE
	char* msgBuff = new char[1000]; //TODO Move this size to the constructor
	char headerBuff[FRAME_HEAD_BYTES];
    char tailBuff[FRAME_TAIL_BYTES];
    uint16_t msgSize;
    char csum;

    //We like to go RAW - this doesnt work
    //struct termios ts_in;
    //tcgetattr(in, &ts_in);
    //cfmakeraw(&ts_in);
    //tcsetattr(in, TCSANOW, &ts_in);

    //Read Header
    if(!readFromSerial(headerBuff, FRAME_HEAD_BYTES)){
        LOG_ERROR << "Couldnt read header \n";
        //TODO Serial Error Handling
    }
    msgSize = GET_MSG_SIZE(headerBuff);

    //Read Msg

    if(!readFromSerial(msgBuff, msgSize)){
        LOG_ERROR << "Couldnt read message \n";
        //TODO Serial Error Handling
    }

    //Read Tail
    if(!readFromSerial(tailBuff, FRAME_TAIL_BYTES)){
        LOG_ERROR << "Couldnt read tail \n";
        //TODO Serial Error Handling
    }

    csum = checksum(msgBuff, msgSize);

    if(tailBuff[0] != END || tailBuff[1] != csum){
        LOG_ERROR << "END of file Missing or Checksum Failed \n";
        //TODO error handling
    }

    return msgBuff;
}

int SerialReceiver::readFromSerial(char *buff, uint32_t size){
    LOG_SCOPE;
	uint32_t bytes_read = 0;
	uint32_t bytes_read_overall = 0;
	do{
		bytes_read = read(in, buff, size-bytes_read_overall); //TODO make qnx readcond
		bytes_read_overall += bytes_read;
	}while(bytes_read >= 0 && bytes_read_overall < size);
	if(bytes_read_overall < size || bytes_read < 0){
        LOG_ERROR << "Error in SerialReceiver, bytes_read: " << bytes_read << " bytes_read_overall: " << bytes_read_overall << " size was: " << size <<"\n";
        return -1;
		//TODO Serial Error Handling
	}
	return 0; //TODO Err handling
}

char SerialReceiver::checksum(char *buff, uint16_t size) {
    char checksum = 0;
    for(int i = 0; i<size; i++){
        checksum |= buff[i];
    }
    return checksum;
}


void SerialReceiver::reset(){
    LOG_SCOPE
    #ifndef WINDOWS
	tcflush(in, TCIOFLUSH);
    #endif
}

void SerialReceiver::operator()(int chid){
    char* buff;
    PulseMessageSenderService pms(chid);
    while(1){ //TODO Make killable
        buff = receive();
        pms.sendPulseMessage((int)buff); //TODO when code ios available, send ser_in
    }
}


