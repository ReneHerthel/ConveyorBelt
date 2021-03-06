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
	uint32_t value;
} pulse;

class ITopLvlProtocoll {
public:
	virtual pulse convToPulse(void *buff) = 0;
	virtual serialized wrapInFrame(int8_t, int32_t) = 0;
private:
    virtual pulse protocollState(int8_t, int32_t) = 0; //TODO Check if usefull
};

#endif /* ITOPLVLPROTOCOLL_H_ */
