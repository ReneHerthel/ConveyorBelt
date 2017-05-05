// =====================================================================================
// LightSystemService.h : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#ifndef LIGHTSYSTEMSERVICE_H
#define LIGHTSYSTEMSERVICE_H

#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "enum.h"
#include "LightSystemController.h"
#include "ILightSystem.h"
#include "Logger.h"
#include "LogScope.h"

class LightSystemService : public ILightSystem {
	public:
		LightSystemService(int coid);
		void setWarningLevel(Level warningLevel);
	private:
		int chid;
} ;

#endif
