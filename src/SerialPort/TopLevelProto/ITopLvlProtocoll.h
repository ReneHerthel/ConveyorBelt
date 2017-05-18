/*
 * ITopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef ITOPLVLPROTOCOLL_H_
#define ITOPLVLPROTOCOLL_H_

typedef struct {
	int_8 code;
	int_32 value;
} pulse;

class ITopLvlProtocoll {
public:
	ITopLvlProtocoll();
	virtual ~ITopLvlProtocoll();

	virtual pulse convToPulse(char* buff) = 0;
	virtual char* wrapInFrame(char* buff) = 0;
};

#endif /* ITOPLVLPROTOCOLL_H_ */
