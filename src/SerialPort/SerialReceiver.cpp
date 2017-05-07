//
// Created by Silt on 07.05.2017.
//

#include "Serial.h"

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
    char* msgBuff;
    char headerBuff[FRAME_HEAD_BYTES];
    char tailBuff[FRAME_TAIL_BYTES];
    uint16_t msgSize;
    char csum;


    //Read Header
    err = read(in, headerBuff, FRAME_HEAD_BYTES); //TODO make qnx readcond
    if(headerBuff[0] != START || err < FRAME_HEAD_BYTES){
        //TODO Serial Error Handling
        cout<< "Failure in Receiver"<<endl;
    }
    msgSize = GET_MSG_SIZE(headerBuff);

    //Read Msg
    msgBuff = new char[msgSize];
    err = read(in, msgBuff, msgSize);
    if(err < msgSize){
        //TODO Serial Error Handling
        cout<< "Failure in Receiver"<<endl;
    }

    //Read Tail
    err = read(in, tailBuff, FRAME_TAIL_BYTES);

    csum = checksum(msgBuff, msgSize);

    if(tailBuff[0] != END || tailBuff[1] != csum){
        //TODO Serial Error Handling
    }

    return msgBuff;
}

char SerialReceiver::checksum(char *buff, uint16_t size) {
    char checksum = 0;
    for(int i = 0; i<size; i++){
        checksum |= buff[i];
    }
    return checksum;
}


