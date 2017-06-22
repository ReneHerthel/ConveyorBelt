/*
 * CodeDefinition.h
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#ifndef CODEDEFINITION_H_
#define CODEDEFINITION_H_

#include "SerialProtocoll.h"
#include "PuckContext.h"
#include "SortingSwichtControl.h"
#include <stdint.h>

namespace CodeDefinition{
	enum Code : uint8_t {
		ISR = 5,

		//v 1 to 4 v
		SER_IN = IN_CODE,                /// Incoming msg from other serial
		SER_OUT = OUT_CODE,              /// Msg from the System to send to the other serial
		TRANSM_IN = TRANSM_IN_CODE,  /// Incoming Transmission of an Puck object
		TRANSM_OUT = TRANSM_OUT_CODE, /// Outgoing Transmission of an Puck object
		//^ 1 to 4 ^

		PUCK_TIMER = TIMERCODE,

		HEIGHT_MEASUREMENT = 0,

		SORTING_SWITCH = SSC_CLOSE

	};
}


#endif /* CODEDEFINITION_H_ */
