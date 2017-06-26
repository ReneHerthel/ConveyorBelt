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
                             SortingSwichtControl &sortingSwichtControl,
                             SerialService &serialService)
    :    m_conveyorBeltService(conveyorBeltService)
    ,    m_heightService(heightService)
    ,    m_sortingSwitchControl(sortingSwichtControl)
	, 	 m_serialService(serialService)
	, 	 lastSpeed(PuckSignal::PuckSpeed::STOP)
{
    // Nothing todo so far.
}

ActorHandler::~ActorHandler()
{
    // Nothing todo so far.
}

void ActorHandler::demultiplex(PuckManager::ManagerReturn &manager)
{
    LOG_SCOPE
    DistanceObservable &distO = DistanceObservable::getInstance();

    if(lastSpeed != manager.speedSignal){

    	switch (manager.speedSignal) {
    	        case PuckSignal::PuckSpeed::STOP:
    	            m_conveyorBeltService.changeState(ConveyorBeltState::STOP);
    	            distO.updateSpeed(DistanceSpeed::STOP);
    	            m_serialService.sendMsg(Serial_n::ser_proto_msg::STOP_SER);
    	            LOG_DEBUG << "[ActorHandler] STOPPED \n";
    	            break;

    	        case PuckSignal::PuckSpeed::SLOW:
    	            m_conveyorBeltService.changeState(ConveyorBeltState::RIGHTSLOW);
    	            m_serialService.sendMsg(Serial_n::ser_proto_msg::RESUME_SER);
    	            distO.updateSpeed(DistanceSpeed::SLOW);
    	            LOG_DEBUG << "[ActorHandler] SLOW \n";
    	            break;

    	        case PuckSignal::PuckSpeed::FAST:
    	            m_conveyorBeltService.changeState(ConveyorBeltState::RIGHTFAST);
    	            m_serialService.sendMsg(Serial_n::ser_proto_msg::RESUME_SER);
    	            distO.updateSpeed(DistanceSpeed::FAST);
    	            LOG_DEBUG << "[ActorHandler] FAST \n";
    	            break;

    	        default:
    	        	 LOG_DEBUG << "[ActorHandler] Cant handle speed, unknown enum " << (int)manager.speedSignal << "\n";
    	            break;
    	}
    }
    lastSpeed = manager.speedSignal;


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
            case PuckManager::SEND_PUCK:
            	m_serialService.sendObj(manager.puckType);
            	break;
            case PuckManager::RECEIVED_PUCK:
            	m_serialService.sendMsg(Serial_n::ser_proto_msg::RECEIVED_SER);
            	break;
            case PuckManager::ACCEPTED_PUCK:
            	m_serialService.sendMsg(Serial_n::ser_proto_msg::ACCEPT_SER);
            	break;
            default:
                // Nothing todo so far.
                break;
        }
    } /* if */
}

/** @} */
