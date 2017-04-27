/*
 * TestLightSystemController.cpp : Test dependency injection and setter
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#include "TestLightSystemHal.h"

using namespace HAL;
using namespace std;

int main(int argc, char *argv[]) {

    // TODO: Readup on parameters
    int coid = ConnectAttach_r(ND_LOCAL_NODE,0,chid,0,0);
    if(coid < 0) {
        // TODO: Dump to log
    }
    TimerService timer = TimerService(chid, code, NULL);
    LightSystemHAL boundary;
    LightSystemController controller = LightSystemController(chid, timer, boundary);
    LightSystemService lightSystem = LightSystemService(chid);
     

    // Set different warning levels
    /* FIXME: Cardinality of enum instead of last definition plus 1 */
    for ( Level warning = OPERATING; warning < CLEAR_ALL+1; warning++ )
    {
        lightSystem.setWarningLevel(warning);
    }
}
