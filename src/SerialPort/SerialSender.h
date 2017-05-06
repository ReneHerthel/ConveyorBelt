/*
 * BSerialSender.h
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#ifndef BSERIALSENDER_H_
#define BSERIALSENDER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <fstream>
#include <limits.h>

#define START  ((char)(1|(1<<7)))
#define END ((char)(4|(1<<7)))
#define CHAR_BITS 8
#define CNTRL_CHAR_BYTES (1)
#define SIZE_BYTES (2)
#define FRAME_HEAD_BYTES (1+SIZE_BYTES)
#define FRAME_BYTES (SIZE_BYTES+CNTRL_CHAR_BYTES*3) //Checksum, END, START

using namespace std;

union frame_buff{
    struct{
        char start;
        uint16_t msgSize;
    };
    char* buff;
};

class SerialSender {
public:
    /**
     * Writes to a Serial Device and wraps in Serial Frame
     * @param path The path to the char device to write to
     */
	SerialSender(string path);
	~SerialSender();

	/*@brief Send a message over the Serial port
	 *
	 *This function takes a massage and send it over the Serial Port
	 *@param[in] msg The Message that will be send over the Serial Port
	 *@return Error Number defined in BSerailSender.h
	 */
	int32_t send(char msg[], uint16_t size);
protected:
	/*@brief Put the Message into a Frame for the Serial Port
	 *
	 *This function takes a massage and build a frame arround it so send over the Serial port.
	 *Frame will be written into the objects buffer
	 *
	 *@param[in] msg The Message that will be put into the frame
	 *@return Size of the frame, including the empty checksum byte
	 */
	int32_t frame(char msg[], uint16_t size);

	/*@brief Calculate Checksum
	 *
	 *Take the bytes from the objects buffer and Calculate a Checksum using XOR
	 *
	 *@param[in] size Size of the frame in the buffer, last byte of the frame (index = size-1) will be used to store the checksum
	 */
	void checksum();

	/*@brief Write the frame to the Serial
	 *
	 *Take the bytes from the objects buffer and send it over the Serial
	 *
	 *@param[in] size Size of the frame in the buffer
	 */
	int32_t sendSerial(uint16_t size);

private:
    fstream outstream; /*!<Filestream to the Charakter Device to send to*/
    uint32_t buffSize;
    frame_buff buff;
};

#endif /* BSERIALSENDER_H_ */
