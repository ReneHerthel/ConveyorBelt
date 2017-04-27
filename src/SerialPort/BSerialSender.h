/*
 * BSerialSender.h
 *
 *  Created on: 27.04.2017
 *      Author: aca619
 */

#ifndef BSERIALSENDER_H_
#define BSERIALSENDER_H_

#include <stdint.h>
#include <string>

using namespace std;

class BSerialSender {
public:
	BSerialSender();
	virtual ~BSerialSender();
	/*@brief Send a message over the Serial port
	 *
	 *This function takes a massage and send it over the Serial Port
	 *@param[in] msg The Message that will be send over the Serial Port
	 *@return Error Number defined in BSerailSender.h
	 */
	in32_t send(string msg);
protected:
	/*@brief Put the Message into a Frame for the Serial Port
	 *
	 *This function takes a massage and build a frame arround it so send over the Serial port.
	 *Frame will be written into the objects buffer
	 *
	 *@param[in] msg The Message that will be put into the frame
	 *@return Size of the frame, so the index of the last bit of the frame (Checksum) is return value -1
	 */
	int32_t frame(string msg);

	/*@brief Calculate Checksum
	 *
	 *Take the bytes from the objects buffer and Calculate a Checksum using XOR
	 *
	 *@param[in] size Size of the frame in the buffer, last byte of the frame (index = size-1) will be used to store the checksum
	 */
	void checksum(int32_t size);

	/*@brief Write the frame to the Serial
	 *
	 *Take the bytes from the objects buffer and send it over the Serial
	 *
	 *@param[in] size Size of the frame in the buffer
	 */
	int32_T sendSerial(int32_t size);
};

#endif /* BSERIALSENDER_H_ */
