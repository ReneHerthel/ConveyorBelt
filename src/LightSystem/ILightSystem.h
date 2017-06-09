/**
 *       @file  ILightSystem.h
 *      @brief  Abstract class to pass commands to LightSystemController
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/07/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef ILIGHTSYSTEM_H
#define ILIGHTSYSTEM_H

#include "LightSystemEnum.h"

class ILightSystem {
	public:
		virtual ~ILightSystem() = 0;
		virtual void setWarningLevel(Level warningLevel) = 0;
};

#endif
