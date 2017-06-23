/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    error_handler
 * @{
 *
 * @brief      Function declaration of the ErrorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ErrorHandler.h"

#include "DistanceObservable.h"
#include "DistanceEnum.h"
#include "Signals.h"

#include <iostream>
using namespace std;
using namespace HAL;

ErrorHandler::ErrorHandler( int chid,
                            ConveyorBeltService &conveyorBeltService,
                            LightSystemService * lightSystemService)
    :    m_hasError(false)
    ,    m_resetPressed(false)
    ,    m_conveyorBeltService(conveyorBeltService)
    ,    m_lightSystemService(lightSystemService)
{
    m_lightSystemService->setWarningLevel(Level::OPERATING);
}

ErrorHandler::~ErrorHandler()
{
    // Nothing todo so far.
}

void ErrorHandler::demultiplex(PuckManager::ManagerReturn &manager)
{
    if (!manager.errorFlag) {
        return; // Do not do anything without a errorFlag.
    }

    m_hasError = true;

    m_lightSystemService->setWarningLevel(Level::ERROR_OCCURED);

    DistanceObservable &distO = DistanceObservable::getInstance();
    distO.updateSpeed(DistanceSpeed::STOP);

    m_conveyorBeltService.changeState(ConveyorBeltState::STOP);

    switch (manager.errorSignal) {

        case PuckManager::ErrorSignal::PUCK_LOST:
            cout << "[ErrorHandler] PUCK_LOST - Late Timer" << endl;
            break;

        case PuckManager::ErrorSignal::PUCK_MOVED:
            cout << "[ErrorHandler] PUCK_MOVED - Puck triggered light barrier before early timer" << endl;
            break;

        case PuckManager::ErrorSignal::UNEXPECTED_SIGNAL:
            cout << "[ErrorHandler] UNEXPECTED_SIGNAL - Signal could not be processed" << endl;
            break;

        case PuckManager::ErrorSignal::MULTIPLE_ACCEPT:
            cout << "[ErrorHandler] MULTIPLE_ACCEPT - Shouldn't happen - multiple pucks were triggered" << endl;
            break;

        case PuckManager::ErrorSignal::MULTIPLE_WARNING:
            cout << "[ErrorHandler] MULTIPLE_WARNING" << endl;
            break;

        default:
            // Nothing todo so far.
            break;
    }
}

bool ErrorHandler::hasError()
{
    return m_hasError;
}

void ErrorHandler::handleMessage(rcv::msg_t message)
{
    bool buttonReset = false;
    bool buttonStart = false;

    if (message.code != 5) { // 5 is hardcoded in the ISR.
        return; // Do not do anything without code 5!
    }

    switch(message.value) {

        case interrupts::BUTTON_RESET:
            buttonReset = true;
            break;

        case interrupts::BUTTON_START:
            buttonStart = true;
            break;

        default:
            // Nothing todo so far.
            break;
    }

    if (buttonReset && m_hasError) {
        m_resetPressed = true;
        cout << "Error acknowledged" << endl;
        m_lightSystemService->setWarningLevel(Level::ERROR_ACKNOWLEDGED);
    }

    if (buttonStart && m_hasError) { // Only go further when reset was pressed before.

        if (m_resetPressed) {
        	cout << "Clear error" << endl;
            m_lightSystemService->setWarningLevel(Level::CLEAR_ERROR);
            m_lightSystemService->setWarningLevel(Level::OPERATING);
            m_resetPressed = false;
        }
        else {
        	cout << "Error gone unacknowledged" << endl;
        	m_lightSystemService->setWarningLevel(Level::ERROR_GONE_UNACKNOWLEDGED);
        }

        m_hasError = false;
    }
}

/** @} */
