/*
 * SerialTopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef SERIALTOPLVLPROTOCOLL_H_
#define SERIALTOPLVLPROTOCOLL_H_

#include "ITopLvlProtocoll.h"

/// Used to dertermin if SerialProtocoll is Sender of receiver
enum Serial_mode {
    RECEIVER,
    SENDER
};

/// Message types that are used to communicate over the serial
enum msg {
    ACCEPT,     /*!<IN: The Receiver accepted Transmission,
                 *OUT: Signal the Receiver that you accept transmission, the puk can be moved */
    STOP,       /*!<IN/OUT: Sender or Receiver signal their counterpart that their belt must be stopped
                 * if there are any Pucks in transmission*/
    RESUME,     /*!<IN/OUT: Sender or Receiver signal their counterpart that their belt should be moved again
                 * Must be send by the participant that send STOP before*/
    INVALID     /*!<IN/OUT The sending participant received Comands in the wrong order*/
};

enum code {
    IN,
    OUT,
    TRANSM_IN,
    TRANSM_OUT
};

class SerialProtocoll : ITopLvlProtocoll {
public:
	SerialProtocoll(Serial_mode mode);
	virtual ~SerialProtocoll();

	pulse convToPulse(char* buff, uint32_t size);
	serialized wrapInFrame(char* buff, uint32_t size);
    serialized wrapInFrame(int8_t int8, int32_t int32) override;
};

#endif /* SERIALTOPLVLPROTOCOLL_H_ */
