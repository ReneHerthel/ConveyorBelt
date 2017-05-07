/*
 * BSerialSender.cpp
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#include <cstring>
#include "Serial.h"

SerialSender::SerialSender(string path) {
    outstream.open(path, ofstream::out | ofstream::binary); //Msg is char based, the Frame is binary, so write binary
    buffSize = sizeof(char)*UCHAR_MAX;
    buff = new char[buffSize];
}

SerialSender::~SerialSender() {
    delete[] buff;
    outstream.close();
}

int32_t SerialSender::send(char *msg, uint16_t size) {
    if((size + FRAME_BYTES) > buffSize){
        delete[] buff;
        buff = new char[size];
    }

    uint16_t framesize = frame(msg, size);
    checksum(framesize);
    sendSerial(framesize);
}

uint16_t SerialSender::frame(char *msg, uint16_t size) {
    memcpy(buff+FRAME_HEAD_BYTES, msg, size);
    SET_START(buff) = START;
    SET_MSG_SIZE(buff) = size;
    buff [FRAME_HEAD_BYTES+size] = END;
    return (uint16_t)(FRAME_HEAD_BYTES+size+1);
}

void SerialSender::checksum(uint16_t size){
    char checksum = 0;
    for(int i = 0+FRAME_HEAD_BYTES; i<(GET_MSG_SIZE(buff))+FRAME_HEAD_BYTES; i++){
        checksum |= buff[i];
    }
    buff[size] = checksum;
}

int32_t SerialSender::sendSerial(uint16_t size) {
    outstream.write(buff, size+1);
}

bool SerialSender::fail() {
    return outstream.fail();
}





