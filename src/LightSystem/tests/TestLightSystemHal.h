/*
 * TestLightSystemHal.h
 *
 *  Created on: 05.04.2017
 *      Author: aca592
 */

#ifndef TESTLIGHTSYSTEMHAL_H_
#define TESTLIGHTSYSTEMHAL_H_

#include "LightSystemHAL.h"

class TestLightSystemHal: public HAL::LightSystemHAL {
	public :
	int main(int argc, char *argv[]);
	void task();
};



#endif /* TESTLIGHTSYSTEMHAL_H_ */
