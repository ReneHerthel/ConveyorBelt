// =====================================================================================
// LightSystemHAL.cpp : Provide methods to hide hardware dependend implementation
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemHAL.h"

namespace HAL {
    void LightSystemHAL::lightOn(Color color) {
        switch (color) {
        case Green:
        case Yellow:
        case Red:
        default:
            // TODO: Pass current function
            stub(color);
        }
    }

    void LightSystemHAL::lightOff(Color color) {
        switch (color) {
        case Green:
        case Yellow:
        case Red:
        default:
            // TODO: Pass current function
            stub(color);
        }
    }
    void LightSystemHAL::stub(Color color) {
        std::cout << color << " stub." << std::endl;
    }
}
