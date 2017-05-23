/*
 * ITopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef ITOPLVLPROTOCOLL_H_
#define ITOPLVLPROTOCOLL_H_

#include <stdint.h>
#include "../ISerializable.h"
typedef struct {
	int8_t code;
	int32_t value;
} pulse;

class ITopLvlProtocoll {
public:
	virtual pulse convToPulse(char* buff, uint32_t size) = 0;
	virtual serialized wrapInFrame(char* buff, uint32_t size) = 0;
	virtual serialized wrapInFrame(int8_t, int32_t) = 0;
    virtual pulse protocollState(int8_t, int32_t) = 0; //TODO Check if usefull
};

#endif /* ITOPLVLPROTOCOLL_H_ */
