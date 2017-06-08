/*
 * SerialTopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef SERIALTOPLVLPROTOCOLL_H_
#define SERIALTOPLVLPROTOCOLL_H_

#include "ITopLvlProtocoll.h"

#define IN_CODE 0x1
#define OUT_CODE 0x2
#define TRANSM_IN_CODE 0x3
#define TRANSM_OUT_CODE 0x4


#define ACCEPT_VAL 		0xFAAA
#define STOP_VAL 		0xFBBB
#define RESUME_VAL 		0xFCCC
#define INVALID_VAL		0xFDDD
#define TRANSM_VAL 		0xFEEE
#define RECEIVED_VAL	0xEFEF
#define POL_VAL 		0xABCD
#define NO_CON_VAL 		0xDBCA
#define ERROR_VAL 		0xFABF

/// Used to dertermin if SerialProtocoll is Sender of receiver
enum Serial_mode {
    RECEIVER,
    SENDER
};

namespace Serial_n{
	/// Message types that are used to communicate over the serial and between serial an system
	enum ser_proto_msg : int32_t {
		ACCEPT_SER  = ACCEPT_VAL,    	/*!<IN: The Receiver accepted Transmission,
									 *OUT: Signal the Receiver that you accept transmission, the puk can be moved */
		STOP_SER    = STOP_VAL,       	/*!<IN/OUT: Sender or Receiver signal their counterpart that their belt must be stopped
									 * if there are any Pucks in transmission*/
		RESUME_SER  = RESUME_VAL,     	/*!<IN/OUT: Sender or Receiver signal their counterpart that their belt should be moved again
									 * Must be send by the participant that send STOP before*/
		INVALID_SER = INVALID_VAL,   	/*!<IN/OUT The sending participant received Comands in the wrong order*/
		TRANSM_SER  = TRANSM_VAL,		/*!<Used only between two serial endpoints to signal an transmission*/
		RECEIVED_SER = RECEIVED_VAL, 	/*!<Signal that a puck was received (detected in light barrier  on other Serial), puck can be deleted */
		POL_SER = POL_VAL, 				/*!<Ping of life */
		NO_CON_SER = NO_CON_VAL, 		/*!<Serial Disconnected, no POL */
		ERROR_SER = ERROR_VAL,			/*!<Serial received something it can not handle, maybe Char loss */
	};

	/// Pulse code identifies in and outgoing signals, transmission need extra code, so the 32Bit pointer can fit into Value
	enum code : int8_t {
	    SER_IN = IN_CODE,                /// Incoming msg from other serial
	    SER_OUT = OUT_CODE,              /// Msg from the System to send to the other serial
	    TRANSM_IN = TRANSM_IN_CODE,  /// Incoming Transmission of an Puck object
	    TRANSM_OUT = TRANSM_OUT_CODE /// Outgoing Transmission of an Puck object
	};
}


class SerialProtocoll : public ITopLvlProtocoll {
public:
	SerialProtocoll(Serial_mode mode);
	virtual ~SerialProtocoll();

    /**
     * Convert an array of bytes to an Code and Value for a pulse message
     * @param buff The arrray of bytes
     * @param size the amount of bytes to read from buff
     * @return struct with code and value, code will be set to IN
     */
	pulse convToPulse(void *buff) override;

    /**
     * Convert to a sendable byte array
     * @param code Type, see enum code, will not be present in the serialized obj
     * @param value Msg, see enum msg, or is a pointer so a serializable ob
     * @return
     */
    serialized wrapInFrame(int8_t code, int32_t value) override;

private:
    pulse protocollState(int8_t int8, int32_t int32) override;
};

#endif /* SERIALTOPLVLPROTOCOLL_H_ */
