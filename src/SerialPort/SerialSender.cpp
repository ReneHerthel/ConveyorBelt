/*
 * BSerialSender.cpp
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#include <cstring>
#include "Serial_def.h"
#include "../Logger/Logger.h"
#include "../Logger/LogScope.h"
#include <fcntl.h>

SerialSender::SerialSender(char *path) {
    out = open(path, O_RDWR | O_CREAT | O_BINARY); //Msg is char based, the Frame is binary, so write binary

   fcntl(out, F_SETFL, 0);

   struct termios ts;
   tcflush(out, TCIOFLUSH);
   tcgetattr(out, &ts);
   cfsetispeed(&ts, B19200);
   cfsetospeed(&ts, B19200);
   ts.c_cflag &= ~CSIZE;
   ts.c_cflag &= ~CSTOPB;
   ts.c_cflag &= ~PARENB;
   ts.c_cflag |= CS8;
   ts.c_cflag |= CREAD;
   ts.c_cflag |= CLOCAL;
   tcsetattr(out, TCSANOW, &ts);
}

SerialSender::~SerialSender() {
    //close(out);
}

int32_t SerialSender::send(char *msg, uint16_t size) {
    LOG_SCOPE
    char buff[size+FRAME_HEAD_BYTES];
    uint16_t framesize = frame(msg, size, buff);
    checksum(framesize, buff);
    sendSerial(framesize, buff);
}

uint16_t SerialSender::frame(char *msg, uint16_t size, char* buff) {
    memcpy(buff+FRAME_HEAD_BYTES, msg, size);
    SET_START(buff) = START;
    SET_MSG_SIZE(buff) = size;
    buff [FRAME_HEAD_BYTES+size] = END;
    return (uint16_t)(FRAME_HEAD_BYTES+size+1);
}

void SerialSender::checksum(uint16_t size, char* buff){
    char checksum = 0;
    for(int i = 0+FRAME_HEAD_BYTES; i<(GET_MSG_SIZE(buff))+FRAME_HEAD_BYTES; i++){
        checksum |= buff[i];
    }
    buff[size] = checksum;
}

int32_t SerialSender::sendSerial(uint16_t size, char* buff) {
    LOG_SCOPE
    err = write(out, buff, size+1);
    if(err < 0){
        LOG_ERROR << "Serial write failed with err code: " << err << "\n";
        //TODO Serial error handling
    }
}

int SerialSender::fail() {
    return err;
}

void SerialSender::reset(){
    LOG_SCOPE
    #ifndef WINDOWS
	tcflush(out, TCIOFLUSH);
    #endif
}





