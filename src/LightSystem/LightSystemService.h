// =====================================================================================
// LightSystemService.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMSERVICE_H
#define LIGHTSYSTEMSERVICE_H

#include "enum.h"
#include "LightSystemController.h"

class LightSystemService : public ILightSystem {
	public:
		void setWarningLevel(Level warningLevel);
	private:
		LightSystemController* controller;
		chid;
} ;

#endif
