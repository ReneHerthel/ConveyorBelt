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

ActorHandler::ActorHandler ( ConveyorBeltService &conveyorBeltService,
							 HeightService &heightService,
                             SortingSwichtControl &sortingSwichtControl )
    :    m_conveyorBeltService(conveyorBeltService)
    ,    m_heightService(heightService)
    ,    m_sortingSwitchControl(sortingSwichtControl)
{
    // Nothing todo so far.
}

ActorHandler::~ActorHandler()
{}

void ActorHandler::demultiplex(PuckManager::ManagerReturn &manager)
{
	LOG_SCOPE
	DistanceObservable &distO = DistanceObservable::getInstance();
	switch (manager.speedSignal) {

	    case PuckSignal::PuckSpeed::STOP:
	    	m_conveyorBeltService.changeState(ConveyorBeltState::STOP);
	    	distO.updateSpeed(DistanceSpeed::STOP);
	    	LOG_DEBUG << "[ActorHandler] STOPPED \n";
	    	break;

	    case PuckSignal::PuckSpeed::SLOW:
            m_conveyorBeltService.changeState(ConveyorBeltState::RIGHTSLOW);
            distO.updateSpeed(DistanceSpeed::SLOW);
            LOG_DEBUG << "[ActorHandler] SLOW \n";
            break;

	    case PuckSignal::PuckSpeed::FAST:
	    	m_conveyorBeltService.changeState(ConveyorBeltState::RIGHTFAST);
	    	distO.updateSpeed(DistanceSpeed::FAST);
	    	LOG_DEBUG << "[ActorHandler] FAST \n";
	    	break;

	    default:
	    	// Nothing todo so far.
	    	break;

	}

    if (manager.actorFlag) {
        switch (manager.actorSignal) {

            case PuckManager::OPEN_SWITCH:
            	LOG_DEBUG << "[ActorHandler] OPEN SWITCH \n";
                m_sortingSwitchControl.open();
                break;

            case PuckManager::START_MEASUREMENT:
            	LOG_DEBUG << "[ActorHandler] START HEIGHT MEASURE \n";
            	m_heightService.startMeasuring();
                break;

            case PuckManager::STOP_MEASUREMENT:
            	LOG_DEBUG << "[ActorHandler] STOP HEIGHT MEASURE \n";
            	m_heightService.stopMeasuring();
                break;

            default:
              // Nothing todo so far.
              break;
        }

    } /* if */
}

/** @} */
