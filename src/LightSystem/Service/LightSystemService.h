/**
 *       @file  LightSystemService.h
 *      @brief  Implement Interface ILightSystem
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/06/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef LIGHTSYSTEMSERVICE_H
#define LIGHTSYSTEMSERVICE_H

#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "LightSystemEnum.h"
#include "LightSystemController.h"
#include "ILightSystem.h"
#include "Logger.h"
#include "LogScope.h"

class LightSystemService : public ILightSystem {
	public:
		LightSystemService(int chid);
		~LightSystemService() {};
        /**
         * @brief  Pass a warning to make the lightsystem blink accordingly
         * @param  [in] warningLevel Warning level to set
         */
		void setWarningLevel(Level warningLevel);
	private:
		int chid; /**< @brief ID for channel LightSystemController object listens on */
} ;

#endif
