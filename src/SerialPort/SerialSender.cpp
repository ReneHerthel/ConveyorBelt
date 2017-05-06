/*
 * BSerialSender.cpp
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#include <cstring>
#include "SerialSender.h"

SerialSender::SerialSender(string path) {
    outstream = fstream(path, fstream::out);
    buffSize = sizeof(char)*UCHAR_MAX;
    buff.buff = new char[buffSize];
}

SerialSender::~SerialSender() {
    delete[] buff.buff;
    outstream.close();
}

int32_t SerialSender::send(char *msg, uint16_t size) {
    if((size + FRAME_BYTES) > buffSize){
        delete[] buff.buff;
        buff.buff = new char[size];
    }

    int32_t framesize = frame(msg, size);
    checksum();

    sendSerial(framesize);
}

int32_t SerialSender::frame(char *msg, uint16_t size) {
    memcpy(buff.buff+FRAME_HEAD_BYTES, msg, size);
    *buff.start = START;
    buff.msgSize = size;
    buff.buff[FRAME_HEAD_BYTES+size] = END;
    return (FRAME_HEAD_BYTES+size+1);
}

void SerialSender::checksum(){
    char checksum = 0;
    for(int i = 0+FRAME_HEAD_BYTES; i<(buff.msgSize)+FRAME_HEAD_BYTES; i++){
        checksum |= buff.buff[i];
    }
    buff.buff[FRAME_HEAD_BYTES+(buff.msgSize)] = END; //TODO Fix Index, needs to be checksum not end
}

int32_t SerialSender::sendSerial(uint16_t size) {
    outstream.write(buff.buff, size);
}





