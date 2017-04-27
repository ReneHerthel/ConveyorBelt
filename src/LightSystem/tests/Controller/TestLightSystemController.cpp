/*
 * TestLightSystemController.cpp : Test dependency injection and setter
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include "TestLightSystemController.h"

using namespace HAL;
using namespace std;

int main(int argc, char *argv[]) {

    // TODO: Readup on parameters
    int coid = ConnectAttach_r(ND_LOCAL_NODE,0,chid,0,0);
    if(coid < 0) {
        // TODO: Dump to log
    }
    ITimer timer = TimerService(chid, code, NULL);
    LightSystemHal boundary = LightSystemHal();
    LightSystemController controller = LightSystemController(chid, timer, boundary);
    LightSystemService lightSystem = LightSystemService(chid);
     

    // Set different warning levels
    /* FIXME: Cardinality of enum instead of last definition plus 1 */
    for ( int warning = OPERATING; warning < CLEAR_ALL+1; warning++ )
    {
        lightSystem.setWarningLevel(warning);
    }
}
