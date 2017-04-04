// =====================================================================================
// LightSystemService.cpp : Service class providing abstract light
// settings
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemService.h"

LightSystemService(LightSystemHAL halObject) {};

void LightSystemService::setLights(Color lightColor, Frequency lightFrequency) {
            if ( !lightFrequency ) {


            } else {
                // TODO: Start timer according to frequency
            }
}

