// =====================================================================================
// LightSystemService.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMSERVICE_H
#define LIGHTSYSTEMSERVICE_H

#include "enum.h"
#include "LightSystemController.h"
#include "ILightSystem.h"

struct LightMessage {
    Color color;
    Frequency frequency;
};

class LightSystemService : public ILightSystem {
	public:
		void setWarningLevel(Level warningLevel);
	private:
		int channelId;
} ;

#endif
