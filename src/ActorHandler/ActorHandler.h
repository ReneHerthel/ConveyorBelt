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
 * @brief      Header declaration of the ActorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_ACTORHANDLER_ACTORHANDLER_H_
#define SRC_ACTORHANDLER_ACTORHANDLER_H_

#include "ConveyorBeltService.h"
#include "Serial.h"
#include "SortingSwichtControl.h"
#include "PuckManager.h"
#include "DistanceObservable.h"
#include "DistanceEnum.h"
#include "HeightService.h"

class ActorHandler
{
public:
    /*
     * @brief Constructor with references to the components.
     */
    ActorHandler(
                  ConveyorBeltService &conveyorBeltService,
                  HeightService &heightService,
                  SortingSwichtControl &sortingSwichtControl
                );

    /*
     * @brief Default destructor.
     */
    ~ActorHandler();

    /*
     * @brief Demultiplex a puck manager and interact with the components.
     *
     * @param[manager] The Puck manager, which contains all needed informations.
     */
    void demultiplex(PuckManager::ManagerReturn &manager);

private:
    /*
     * @brief A reference to the ConveyorBelt component.
     */
    ConveyorBeltService &m_conveyorBeltService;

    /*
     * @brief A reference to the HeightMeasurement component.
     */
    HeightService &m_heightService;

    /*
     * @brief A reference to the SortingSwitchtControll component.
     */
    SortingSwichtControl &m_sortingSwitchControl;
};

#endif /* SRC_ACTORHANDLER_ACTORHANDLER_H_ */
/** @} */
