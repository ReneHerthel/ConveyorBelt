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

    LOG_DEBUG << "[ActorHandler] lastspeed " << lastSpeed << " manger speed " << manager.speedSignal << "\n" ;

    ConveyorBeltState newCbsSpeed;
    DistanceSpeed::speed_t newDistanceTrackerSpeed;
    Serial_n::ser_proto_msg newSerialMsg;

    switch (manager.speedSignal) { //Choose the wanted signals
        	        case PuckSignal::PuckSpeed::STOP:
        	            LOG_DEBUG << "[ActorHandler] STOPPED \n";
        	            newCbsSpeed = ConveyorBeltState::STOP;
        	            newDistanceTrackerSpeed = DistanceSpeed::STOP;
        	            newSerialMsg = Serial_n::ser_proto_msg::STOP_SER;
        	            break;

        	        case PuckSignal::PuckSpeed::SLOW:
        	            LOG_DEBUG << "[ActorHandler] SLOW \n";
        	            newCbsSpeed = ConveyorBeltState::RIGHTSLOW;
        	            newDistanceTrackerSpeed = DistanceSpeed::SLOW;
        	            newSerialMsg = Serial_n::ser_proto_msg::RESUME_SER;
        	            break;

        	        case PuckSignal::PuckSpeed::FAST:
        	            LOG_DEBUG << "[ActorHandler] FAST \n";
        	            newCbsSpeed = ConveyorBeltState::RIGHTFAST;
        	            newDistanceTrackerSpeed = DistanceSpeed::FAST;
        	            newSerialMsg = Serial_n::ser_proto_msg::RESUME_SER;
        	            break;

        	        default:
        	        	LOG_DEBUG << "[ActorHandler] Cant set speed, unknown enum " << (int)manager.speedSignal << "\n";
        	            break;
    }

    //Set updated speeds
    m_conveyorBeltService.changeState(newCbsSpeed);
    distO.updateSpeed(newDistanceTrackerSpeed);


    //Only send over serial if something changed
	if(lastSpeed != manager.speedSignal){
		m_serialService.sendMsg(newSerialMsg);
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
            case PuckManager::SEND_SLIDE_FULL:
            	m_serialService.sendMsg(Serial_n::ser_proto_msg::SLIDE_FULL_SER);
            	break;
            default:
            	LOG_DEBUG << "[ActorHandler] Cant set actor, unknown enum " << (int)manager.speedSignal << "\n";
                break;
        }
    } /* if */
}

/** @} */
