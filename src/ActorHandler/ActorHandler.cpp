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

ActorHandler::ActorHandler ( ConveyorBeltService * conveyorBeltService,
                             HeightMeasurementService * heightMeasurementService,
                             Serial * serial,
                             SortingSwichtControl * sortingSwichtControl )

    :    m_conveyorBeltService(conveyorBeltService)
    ,    m_heightMeasurementService(heightMeasurementService)
    ,    m_serial(serial)
    ,    m_sortingSwitchControl(sortingSwichtControl)
{
    // Nothing todo so far.
}

ActorHandler::~ActorHandler()
{
	delete m_conveyorBeltService;
	delete m_heightMeasurementService;
	delete m_serial;
	delete m_sortingSwitchControl;
}

void ActorHandler::demultiplex(PuckManager::ManagerReturn * manager)
{
	if (manager->errorFlag) {

	}

	if (manager->actorFlag) {

	}
    switch (manager->actorSignal) {

        case PuckManager::OPEN_SWITCH:
            break;
    }
}

/** @} */
