/*
 * TestLightSystemController.h : Test dependency injection and setter
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "LightSystemEnum.h"
#include "Logger.h"
#include "LogScope.h"
#include "LightSystemController.h"
#include "LightSystemHal.h"
#include "LightSystemService.h"

#define PAUSE_TIME 10
#define LS_MODULE_ID 5
