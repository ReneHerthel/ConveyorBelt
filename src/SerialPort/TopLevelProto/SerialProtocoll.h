/*
 * SerialTopLvlProtocoll.h
 *
 *  Created on: 18.05.2017
 *      Author: aca619
 */

#ifndef SERIALTOPLVLPROTOCOLL_H_
#define SERIALTOPLVLPROTOCOLL_H_

class SerialProtocoll : ITopLvlProtocoll {
public:
	SerialProtocoll();
	virtual ~SerialProtocoll();

	virtual pulse convToPulse(char* buff);
	virtual char* wrapInFrame(char* buff);
};

#endif /* SERIALTOPLVLPROTOCOLL_H_ */
