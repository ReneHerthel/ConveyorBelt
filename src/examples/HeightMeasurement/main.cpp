/*
 * main.cpp
 *
 *  Created on: 09.05.2017
 *      Author: René Herthel
 */

#include "TestHeightMeasurement.h"

#include <hw/inout.h>
#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>

int main(void) {

    // trying to get right access to the I/O hardware
    if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1)
    {
        std::cout << "Can't get Hardware access, therefore can't do anything." << std::endl;
        return EXIT_FAILURE;
	}

	TestHeightMeasurement test;

    test.startTest();

	return 0;
}

