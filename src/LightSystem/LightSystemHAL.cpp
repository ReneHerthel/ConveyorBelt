// =====================================================================================
// LightSystemHAL.cpp : Provide methods to hide hardware dependend implementation
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemHAL.h"

// FIXME: Move declarations to header file
namespace HAL {
    void LightSystemHAL::lightOn(Color color) {
        switch (color) {
        case Green:
            ;
        }
        stub();
    }

    void LightSystemHAL::lightOff(Color color) {
        switch (color) {
        case Green:
            ;
        }
        stub();
    }
    void LightSystemHAL::stub(void) {
        std::cout << "Stub." << std::endl;
    }
}
