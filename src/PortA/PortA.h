/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    port_a
 * @{
 *
 * @brief      Header definition of the PortA as singleton
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_PORTA_PORTA_H_
#define SRC_PORTA_PORTA_H_

/** TODO: Explain purpose */
#define CTRL_REG_GROUP0     0x303
/*
 * PORT A : OUTPUT
 * PORT B : INPUT
 * PORT C Lo : OUTPUT
 * PORT C Hi : INPUT
 * Mode Select : 00
 */
/** TODO: Explain purpose */
#define DEFAULT_PORTS_SETTINGS 0x8A

#include <mutex>
#include <stdint.h>

class PortA
{
public:
    /*
     * @brief Get the instance of the PortA singleton.
     *
     * @return[portA] The reference to the singleton.
     */
    static PortA& getInstance();

    /*
     * @brief Set the corresponding bit in Port A.
     */
    void bitSet(uint8_t bit);

    /*
     * @brief Clear the corresponding bit in Port A.
     */
    void bitClear(uint8_t bit);

    /*
     * @brief Read the corresponding bit from Port A.
     *
     * @return 0 on bit is clear. 1 on bit is set. -1 on random error.
     */
    int bitRead(uint8_t bit);

private:
    /*
     * @brief Hidden constructor, which set the default port settings.
     */
    PortA();

    /*
     * @brief Hidden copy constructor.
     */
    PortA(PortA const&);

    /*
     * @brief Hidden Assign operator.
     */
    PortA& operator=(PortA const&);

    /*
     * @brief Hidden destructor.
     */
    ~PortA(){};

    /*
     * @brief The mutex, where the singleton locks.
     */
    std::mutex m_mutex;
};

#endif /* SRC_PORTA_PORTA_H_ */
/** @} */
