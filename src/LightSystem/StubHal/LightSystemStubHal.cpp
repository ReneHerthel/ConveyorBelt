// =====================================================================================
// LightSystemStubHal.cpp : 
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemStubHal.h"

using namespace std;

namespace HAL {
    void LightSystemStubHal::lightOn(Color color) {
        cout << __FUNCTION__ << ": " << color << endl;
    }
    void LightSystemStubHal::lightOff(Color color) {
        cout << __FUNCTION__ << ": " << color << endl;
    }
}
