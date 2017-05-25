//
// Created by Silt on 07.05.2017.
//

#include "Serial.h"
#include "SerialReceiver.h"

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
	char* msgBuff = new char[1000]; //TODO define
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
    readFromSerial(headerBuff, FRAME_HEAD_BYTES);

    msgSize = GET_MSG_SIZE(headerBuff);

    //Read Msg

    readFromSerial(msgBuff, msgSize);

    //Read Tail
    readFromSerial(tailBuff, FRAME_TAIL_BYTES);

    csum = checksum(msgBuff, msgSize);

    if(tailBuff[0] != END || tailBuff[1] != csum){
        //TODO Serial Error Handling
    }

    return msgBuff;
}

int SerialReceiver::readFromSerial(char *buff, uint32_t size){
	uint32_t bytes_read = 0;
	uint32_t bytes_read_overall = 0;
	do{
		bytes_read = read(in, buff, size-bytes_read_overall); //TODO make qnx readcond
		bytes_read_overall += bytes_read;
	}while(bytes_read >= 0 && bytes_read_overall < size);
	if(bytes_read_overall < size){
		//TODO Serial Error Handling
		cout<< "Failure in Receiver, read " << bytes_read_overall << " bytes"<<endl;
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
    #ifndef WINDOWS
	tcflush(in, TCIOFLUSH);
    #endif
}


