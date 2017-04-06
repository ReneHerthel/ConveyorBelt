// =====================================================================================
// ILightSystem.h : Abstract class to pass commands to LightSystemController
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef ILIGHTSYSTEM_H
#define ILIGHTSYSTEM_H

#include "enum.h"

class ILightSystem {
	public:
		virtual void setWarningLevel(Level warningLevel) = 0;
};

#endif
