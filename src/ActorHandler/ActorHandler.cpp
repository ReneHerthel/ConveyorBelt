/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    actor_handler
 * @{
 *
 * @brief      Function declaration of the ActorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "ActorHandler.h"

ActorHandler::ActorHandler ( ConveyorBeltService * conveyorBeltService,
                             HeightMeasurementService * heightMeasurementService,
                             SortingSwichtControl * sortingSwichtControl )
    :    m_conveyorBeltService(conveyorBeltService)
    ,    m_heightMeasurementService(heightMeasurementService)
    ,    m_sortingSwitchControl(sortingSwichtControl)
{
    // Nothing todo so far.
}

ActorHandler::~ActorHandler()
{
	delete m_conveyorBeltService;
	delete m_heightMeasurementService;
	delete m_sortingSwitchControl;
}

void ActorHandler::demultiplex(PuckManager::ManagerReturn * manager)
{
	if (manager->actorFlag != 1) {

        switch (manager->actorSignal) {

            case PuckManager::OPEN_SWITCH:
                m_sortingSwitchControl->open();
                break;

            case PuckManager::START_MEASUREMENT:
                m_heightMeasurementService->startMeasuring();
        	    break;

            case PuckManager::STOP_MEASUREMENT:
                m_heightMeasurementService->stopMeasuring();
        	    break;

            default:
        	    // Nothing todo so far.
        	    break;
        }

	} /* if */
}

/** @} */
