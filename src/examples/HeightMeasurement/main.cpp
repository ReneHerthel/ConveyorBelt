/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Main of the HeightMeasurement example application.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
 */

#include "TestHeightMeasurement.h"

#include <hw/inout.h>
#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>

int main(void) {
    // trying to get right access to the I/O hardware
    int err = ThreadCtl(_NTO_TCTL_IO_PRIV, 0);

    if (err < 0) {
        std::cout << "[TestHeightMeasurement] main() I/O access failed." << std::endl;
        return EXIT_FAILURE;
    }

    TestHeightMeasurement test;
    test.startTest();

    return 0;
}

/** @}*/
