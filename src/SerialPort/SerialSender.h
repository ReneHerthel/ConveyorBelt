/*
 * BSerialSender.h
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#ifndef BSERIALSENDER_H_
#define BSERIALSENDER_H_

#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <limits.h>
#include <fcntl.h>

using namespace std;

class SerialSender {
public:
    /**
     * Writes to a Serial Device and wraps in Serial Frame
     * @param path The path to the char device to write to
     */
    SerialSender(char *path);
	~SerialSender();

	/**
	 * @brief Send a message over the Serial port
	 *
	 *This function takes a massage and send it over the Serial Port
	 *@param[in] msg The Message that will be send over the Serial Port
	 *@return Error Number defined in BSerailSender.h
	 */
	int32_t send(char msg[], uint16_t size);

    /**
     * Check if the construction failed
     * @return success
     */
    int fail();

    /**
     * Reset the Receiver and Serial buffers
     */
    void reset();

protected:
	/*@brief Put the Message into a Frame for the Serial Port
	 *
	 *This function takes a massage and build a frame arround it so send over the Serial port.
	 *Frame will be written into the objects buffer
	 *
	 *@param[in] msg The Message that will be put into the frame
	 *@return Size of the frame, including the empty checksum byte
	 */
	uint16_t frame(char msg[], uint16_t size, char *buff);

	/*@brief Calculate Checksum
	 *
	 *Take the bytes from the objects buffer and Calculate a Checksum using XOR
	 *
	 *@param[in] size Size of the frame in the buffer, last byte of the frame (index = size-1) will be used to store the checksum
	 */
	void checksum(uint16_t size, char *buff);

	/*@brief Write the frame to the Serial
	 *
	 *Take the bytes from the objects buffer and send it over the Serial
	 *
	 *@param[in] size Size of the frame in the buffer
	 */
	int32_t sendSerial(uint16_t size, char *buff);

private:
    int out; /*!<Filestream to the Charakter Device to send to*/
    int err; /*!<Err from IO */
};

#endif /* BSERIALSENDER_H_ */
