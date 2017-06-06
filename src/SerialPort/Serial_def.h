//
// Created by Silt on 07.05.2017.
//

#ifndef CONVEYORBELT_SERIAL_H_H
#define CONVEYORBELT_SERIAL_H_H

#define START  ((char)(1|(1<<7))) //129 -127
#define END ((char)(4|(1<<7))) //132  -124
#define CHAR_BITS 8
#define CNTRL_CHAR_BYTES (1)
#define SIZE_BYTES (2)
#define FRAME_HEAD_BYTES (1+SIZE_BYTES)
#define FRAME_TAIL_BYTES (2)
#define FRAME_BYTES (FRAME_HEAD_BYTES+FRAME_TAIL_BYTES) //Checksum, END, START
#define SET_START(buff) (*buff)
#define SET_MSG_SIZE(buff) uint16_t* tmp = ((uint16_t*)(buff+1)); (*tmp)
#define GET_MSG_SIZE(buff) ((uint16_t)(*(buff+1)))

#include "SerialSender.h"
#include "SerialReceiver.h"

//FRAME DEFINITION [START][SIZE][SIZE][MSG]...[MSG][END][CHECKSUM]

#endif //CONVEYORBELT_SERIAL_H_H
