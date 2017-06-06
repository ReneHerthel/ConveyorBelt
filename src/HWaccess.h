/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    hw
 * @{
 *
 * @brief      All needed header files to access the hardware.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HWACCESS_H_
#define HWACCESS_H_

#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/inout.h>

/*
 * @brief Switch between simulation and h if needed.
 */
#ifdef SIMULATION
#include <ioaccess.h>
#endif


#endif /* HWACCESS_H_ */
/** @} */
