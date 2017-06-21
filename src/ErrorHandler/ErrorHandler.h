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
 * @brief      Header declaration of the ErrorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_ERRORHANDLER_ERRORHANDLER_H_
#define SRC_ERRORHANDLER_ERRORHANDLER_H_

#include "PuckManager.h"
#include "ConveyorBeltService.h"
#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"
#include "LightSystemService.h"
#include "LightSystemHal.h"
#include "LightSystemController.h"

class ErrorHandler {
public:
    /*
     * @brief Default constructor.
     */
    ErrorHandler(int chid, ConveyorBeltService &conveyorBeltService, LightSystemService * lightSystemService);

    /*
     * @brief Default destructor.
     */
    ~ErrorHandler();

    /*
     * @brief demultiplex the error flags of the puck manager.
     */
    void demultiplex(PuckManager::ManagerReturn &manager);

    /*
     * @brief return if there is actual an error.
     */
    bool hasError();

    /*
     * @brief Handle incoming pulse messages as error.
     */
    void handleMessage(rcv::msg_t message);

private:
    /*
     * @brief Remember if there was an error.
     */
    bool m_hasError;

    /*
     * @brief Remember if the Reset-Button was pressed
     */
    bool m_resetPressed;

    /*
     * @brief A reference to the ConveyorBelt.
     */
    ConveyorBeltService &m_conveyorBeltService;

    /*
     * @brief A reference to the LightSystem.
     */
    LightSystemService * m_lightSystemService;

};

#endif /* SRC_ERRORHANDLER_ERRORHANDLER_H_ */
/** @} */
