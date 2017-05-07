//
// Created by Silt on 07.05.2017.
//

#include "Serial.h"

SerialReceiver::SerialReceiver(string path) {
    instream.open(path, ofstream::in);
}

SerialReceiver::~SerialReceiver() {
    instream.close();
}

bool SerialReceiver::fail() {
    return instream.fail();
}

char* SerialReceiver::receive() {
    char* msgBuff;
    char headerBuff[FRAME_HEAD_BYTES];
    char tailBuff[FRAME_TAIL_BYTES];
    uint16_t msgSize;
    char csum;

    instream.read(headerBuff, FRAME_HEAD_BYTES);
    if(headerBuff[0] != START || instream.fail()){
        //TODO Serial Error Handling
        cout<< "Failure in Receiver"<<endl;
    }
    msgSize = GET_MSG_SIZE(headerBuff);

    msgBuff = new char[msgSize];
    instream.read(msgBuff, msgSize);
    instream.read(tailBuff, FRAME_TAIL_BYTES);

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


