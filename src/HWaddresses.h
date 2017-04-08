/*
* Copyright (C) 2017 Rene Herthel
*
* This file is subject to the terms and conditions of the MIT License.
* See the file LICENSE in the top level directory for more details.
*/

/**
 * @ingroup    register
 * @{
 *
 * @brief      Hardware register addresses. 
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HW_ADDRESSES_H_
#define HW_ADDRESSES_H_

/**
 * @brief The base address of port A.
 */
#define PORTA_REG_ADDR 0x300

/**
 * @brief The base address of port B.
 */
#define PORTB_REG_ADDR 0x301

/**
 * @brief The base address of port C.
 */
#define PORTC_REG_ADDR 0x302

/**
 * @brief Controll register of group 0.
 */
#define CTRL_REG_GROUP0 0x303

/**
 * @brief The default port settings.
 */
#define DEFAULT_PORT_SETTINGS 0x8A

#endif /* HW_ADDRESSES_H_ */
/** @} */
