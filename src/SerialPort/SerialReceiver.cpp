//
// Created by Silt on 07.05.2017.
//

#include "Serial_def.h"
#include "SerialReceiver.h"
#include "../Logger/Logger.h"
#include "../Logger/LogScope.h"
#include "../Wrapper/PulseMessageSender/IPulseMessageSender.h"
#include "../Wrapper/PulseMessageSender/PulseMessageSenderService.h"
#include "SerialProtocoll.h"

SerialReceiver::SerialReceiver(char *path_):
    path(path_)
{
    in = open(path.c_str(), O_RDWR | O_CREAT | O_BINARY);
    fcntl(in, F_SETFL, 0);

    fcntl(in, F_SETFL, 0);
    struct termios ts;
    tcflush(in, TCIOFLUSH);
    tcgetattr(in, &ts);
    cfsetispeed(&ts, B19200);
    cfsetospeed(&ts, B19200);
    ts.c_cflag &= ~CSIZE;
    ts.c_cflag &= ~CSTOPB;
    ts.c_cflag &= ~PARENB;
    ts.c_cflag |= CS8;
    ts.c_cflag |= CREAD;
    ts.c_cflag |= CLOCAL;
    tcsetattr(in, TCSANOW, &ts);
}

SerialReceiver::~SerialReceiver() {
    close(in);
}

int SerialReceiver::fail() {
    return err;
}

char* SerialReceiver::receive() {
	reset();
    LOG_SCOPE
	char* msgBuff = new char[1000]; //TODO Move this size to the constructor
	char headerBuff[FRAME_HEAD_BYTES];
    char tailBuff[FRAME_TAIL_BYTES];
    uint16_t msgSize;
    char csum;

    //Read Header
    if(readFromSerial(headerBuff, FRAME_HEAD_BYTES) != 0){
        LOG_ERROR << "Couldnt read header \n";
        delete[]msgBuff;
        return NULL;
    }
    msgSize = GET_MSG_SIZE(headerBuff);

    //Read Msg

    if(readFromSerial(msgBuff, msgSize) != 0){
        LOG_ERROR << "Couldnt read message \n";
        delete[]msgBuff;
        return NULL;
    }

    //Read Tail
    if(readFromSerial(tailBuff, FRAME_TAIL_BYTES) != 0){
        LOG_ERROR << "Couldnt read tail \n";
        delete[]msgBuff;
        return NULL;
    }

    csum = checksum(msgBuff, msgSize);

    if(tailBuff[0] != END || tailBuff[1] != csum){
        LOG_ERROR << "END of file Missing or Checksum Failed \n";
        delete[]msgBuff;
        return NULL;
    }

    return msgBuff;
}

int SerialReceiver::readFromSerial(char *buff, uint32_t size){
    LOG_SCOPE;
	uint32_t bytes_read = 0;

    bytes_read = readcond(in, buff, size, size, 0, 60); //return with less then size bytes when SER_REC_TIMEOUT has expired, or size bytes when size bytes are available.

	if(bytes_read < size || bytes_read < 0){
        LOG_ERROR << "Error in SerialReceiver, bytes_read: " << bytes_read << " size was: " << size <<"\n";
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
    LOG_SCOPE
    PulseMessageSenderService pms(chid);
	char* buff;
    running = true;
    in = open(path.c_str(), O_RDWR | O_CREAT | O_BINARY);
    while(running){
        buff = receive();
        if(buff == NULL){
        	pms.sendPulseMessage(SER_REC_FAIL, (const int) buff);
        } else {
        	pms.sendPulseMessage(SER_REC_IN, (const int) buff);
        }

    }

}

void SerialReceiver::kill() {
    running = false;
}


