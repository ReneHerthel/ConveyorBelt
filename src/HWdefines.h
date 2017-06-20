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
  * @brief      Handy hardware definitions.
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef HWDEFINES_H_
#define HWDEFINES_H_

/*
 * @brief The pin defintions.
 */
#define PIN_0              0
#define PIN_1              1
#define PIN_2              2
#define PIN_3              3
#define PIN_4              4
#define PIN_5              5
#define PIN_6              6
#define PIN_7              7

/*
 * @brief The specific port addresses.
 */
#define PORT_ADDR_A        0x300
#define PORT_ADDR_B        0x301
#define PORT_ADDR_C        0x302
#define PORT_ADDR_AIO      0x320
#define PORT_ADDR_DIO      0x300

/*
 * @brief The mask of the Led pins.
 */
#define LED_START_MASK     0x01
#define LED_RESET_MASK     0x02
#define LED_Q1_MASK        0x04
#define LED_Q2_MASK        0x08

/*
 * @brief Masks of the Engine.
 */
#define ENGINE_REG_MASK    0x0F
#define ENGINE_RIGHT_MASK  0x01
#define ENGINE_LEFT_MASK   0x02
#define ENGINE_SLOW_MASK   0x04
#define ENGINE_STOP_MASK   0x08

/*
 * @brief Mask of the SortingSwitch.
 */
#define SORTING_SWITCH_MASK 0x10

/*
 * @brief Defines for the AIO port.
 */
#define HEIGHT_MEASUREMENT_OFFSET_LOW_BYTE    0x02
#define HEIGHT_MEASUREMENT_START_CODE         0x10
#define HEIGHT_MEASUREMENT_OFFSET_HIGH_BYTE   0x03

#define CTRL_REG_GROUP0     0x303
#define DEFAULT_PORTS_SETTINGS 0x8A

#endif /* HWDEFINES_H_ */
/** @} */
