// =====================================================================================
// LightSystemController.cpp : Controller sets Lights according to
// warning level
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

LightSystemController(LightSystemController* serviceId) :
serviceId(
{};

void LightSystemService::setLights(Color lightColor, Frequency lightFrequency) {
            if ( !lightFrequency ) {
                halObject.lightOn(lightColor);
            } else {
                // TODO: Start timer according to frequency
            }
}
