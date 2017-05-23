/*
 * SerialTopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef SERIALTOPLVLPROTOCOLL_H_
#define SERIALTOPLVLPROTOCOLL_H_

#include "ITopLvlProtocoll.h"

#define IN_CODE 21
#define OUT_CODE 22
#define TRANSM_IN_CODE 23
#define TRANSM_OUT_CODE 24

/// Used to dertermin if SerialProtocoll is Sender of receiver
enum Serial_mode {
    RECEIVER,
    SENDER
};

/// Message types that are used to communicate over the serial
enum msg : int32_t {
    ACCEPT,     /*!<IN: The Receiver accepted Transmission,
                 *OUT: Signal the Receiver that you accept transmission, the puk can be moved */
    STOP,       /*!<IN/OUT: Sender or Receiver signal their counterpart that their belt must be stopped
                 * if there are any Pucks in transmission*/
    RESUME,     /*!<IN/OUT: Sender or Receiver signal their counterpart that their belt should be moved again
                 * Must be send by the participant that send STOP before*/
    INVALID     /*!<IN/OUT The sending participant received Comands in the wrong order*/
};

/// Pulse code identifies in and outgoing signals, transmission need extra code, so the 32Bit pointer can fit into Value
enum code : int8_t {
    IN = IN_CODE,                /// Incoming msg from other serial
    OUT = OUT_CODE,              /// Msg from the System to send to the other serial
    TRANSM_IN = TRANSM_IN_CODE,  /// Incoming Transmission of an Puck object
    TRANSM_OUT = TRANSM_OUT_CODE /// Outgoing Transmission of an Puck object
};

class SerialProtocoll : ITopLvlProtocoll {
public:
	SerialProtocoll(Serial_mode mode);
	virtual ~SerialProtocoll();

    /**
     * Convert an array of bytes to an Code and Value for a pulse message
     * @param buff The arrray of bytes
     * @param size the amount of bytes to read from buff
     * @return struct with code and value
     */
	pulse convToPulse(char* buff, uint32_t size) override;
    serialized wrapInFrame(char* buff, uint32_t size) override;

    /**
     * Convert to a sendable byte array
     * @param code Type, see enum code
     * @param value Msg, see enum msg, or is a pointer so a serializable ob
     * @return
     */
    serialized wrapInFrame(int8_t code, int32_t value) override;
};

#endif /* SERIALTOPLVLPROTOCOLL_H_ */
