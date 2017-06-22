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
    m_lightSystemService->setWarningLevel(Level::CLEAR_ALL);
    m_lightSystemService->setWarningLevel(Level::OPERATING);
}

ErrorHandler::~ErrorHandler()
{
    // Nothing todo so far.
}

void ErrorHandler::demultiplex(PuckManager::ManagerReturn &manager)
{
    if (manager.errorFlag) {

        m_lightSystemService->setWarningLevel(Level::CLEAR_ALL);
        m_lightSystemService->setWarningLevel(Level::ERROR_OCCURED);

        m_hasError = true;

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
    } /* if */
}

bool ErrorHandler::hasError()
{
    return m_hasError;
}

void ErrorHandler::handleMessage(rcv::msg_t message)
{
    if (message.code == 5) { // 5 is hardcoded in the ISR

        switch(message.value) {

            case interrupts::BUTTON_RESET:
                cout << "[ErrorHandler] BUTTON_RESET pressed" << endl;
                if (m_hasError) {
                    m_resetPressed = true;
                    m_lightSystemService->setWarningLevel(Level::CLEAR_ALL);
                    m_lightSystemService->setWarningLevel(Level::ERROR_ACKNOWLEDGED);
                }
                break;

            case interrupts::BUTTON_START:
                cout << "[ErrorHandler] BUTTON_START pressed" << endl;
                if (m_resetPressed) {
                    m_hasError = false;
                    m_resetPressed = false;
                    m_lightSystemService->setWarningLevel(Level::CLEAR_ALL);
                    m_lightSystemService->setWarningLevel(Level::OPERATING);
                }
                break;

            default:
                // Nothing todo so far.
                break;
        }
    } /* if */
}

/** @} */
