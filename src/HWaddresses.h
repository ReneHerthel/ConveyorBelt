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
#define PORTA_REG_ADDR               0x300

/**
 * @brief The base address of port B.
 */
#define PORTB_REG_ADDR               0x301

/**
 * @brief The base address of port C.
 */
#define PORTC_REG_ADDR               0x302

/**
 * @brief Controll register of group 0.
 */
#define CTRL_REG_GROUP0              0x303

/**
 * @brief The default port settings.
 */
#define DEFAULT_PORT_SETTINGS        0x8A

/*
 * @brief Engine bit masks.
 */
#define ENGINE_REG_MASK              0x0F
#define ENGINE_RIGHTFAST_REG_MASK    0x01
#define ENGINE_RIGHTSLOW_REG_MASK    0x05
#define ENGINE_LEFTFAST_REG_MASK     0x02
#define ENGINE_LEFTSLOW_REG_MASK     0x06
#define ENGINE_STOP_REG_MASK         0x08

/*
 * @brief LED bit masks.
 */
#define LED_REG_MASK                 0x0F
#define LED_START_REG_MASK           0x01
#define LED_RESET_REG_MASK           0x02
#define LED_Q1_REG_MASK              0x04
#define LED_Q2_REG_MASK              0x08

/*
 * @brief Buttons bit masks.
 */
#define BUTTON_REG_MASK              0xF0
#define BUTTON_START_REG_MASK        0x10
#define BUTTON_STOP_REG_MASK         0x20
#define BUTTON_RESET_REG_MASK        0x40
#define BUTTON_E_STOP_REG_MASK       0x80

/*
 *@brief Light Barriers bit masks.
 */
#define LB_REG_MASK                  0xE7
#define LB_INLET_REG_MASK            0x01
#define LB_IN_MEASUREMENT_REG_MASK   0x02
#define LB_IN_SWITCH_REG_MASK        0x04
#define LB_SWITCH_OPEN_REG_MASK      0x20
#define LB_SLIDE_FULL_REG_MASK       0x40
#define LB_OUTLET_REG_MASK           0x80

/*
 * @brief Metal Detector bit masks.
 */
#define MD_IS_METAL                  0x10

/*
 * @brief Light Signal bit masks.
 */
#define LIGHT_SIGNAL_REG_MASK        0xE0
#define LIGHT_SIGNAL_GREEN_REG_MASK  0x20
#define LIGHT_SIGNAL_YELLOW_REG_MASK 0x40
#define LIGHT_SIGNAL_RED_REG_MASK    0x80


#endif /* HW_ADDRESSES_H_ */
/** @} */
