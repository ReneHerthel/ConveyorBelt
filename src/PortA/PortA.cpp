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

#include "PortA.h"
#include "HWdefines.h"
#include "HWaccess.h"

PortA::PortA()
{
    out8(CTRL_REG_GROUP0, DEFAULT_PORTS_SETTINGS);
}

PortA::~PortA()
{
	// Just to be sure.
    m_mutex.unlock();
}

PortA& PortA::getInstance()
{
    static PortA instance;
    return instance;
}

void PortA::bitSet(uint8_t bit)
{
    m_mutex.lock();
	LOG_DEBUG << "[PortA] Set bits" << std::endl;
    out8(PORT_ADDR_A, (in8(PORT_ADDR_A) | bit));
    m_mutex.unlock();
}

void PortA::bitClear(uint8_t bit)
{
    m_mutex.lock();
	LOG_DEBUG << "[PortA] Clear bits" << std::endl;
    out8(PORT_ADDR_A, (in8(PORT_ADDR_A) & ~(bit)));
    m_mutex.unlock();
}

int PortA::bitRead(uint8_t bit)
{
    int ret = -1;
    m_mutex.lock();
    ret = in8(PORT_ADDR_A) & bit;
    m_mutex.unlock();
    return ret;
}

/** @}*/
