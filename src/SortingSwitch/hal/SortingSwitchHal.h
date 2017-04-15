/*
 * SortingSwitchHal.h
 *
 *  Created on: 12.04.2017
 *      Author: abo000
 */

#ifndef SORTINGSWITCHHAL_H_
#define SORTINGSWITCHHAL_H_

#include "BSortingSwitch.h"

class SortingSwitchHal : public BSortingSwitch {
public:

	/*
	 * @brief Default constructor.
	 */
	SortingSwitchHal(const int port);

	void setPin(const int pin);
	void clearPin(const int pin);

private:
	int port_;
};

#endif /* SORTINGSWITCHHAL_H_ */
