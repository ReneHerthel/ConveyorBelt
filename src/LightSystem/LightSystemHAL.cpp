// =====================================================================================
// LightSystemHAL.cpp : Provide methods to hide hardware dependend implementation
// 
//    Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "enum.h"
#include <iostream>

namespace HAL {
    class LightSystemHAL {
        public:
            void lightOn(Color color);
            void lightOff(Color color);
        private:
            void stub(void);
    };

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
