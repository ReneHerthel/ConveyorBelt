// =====================================================================================
//
//       Filename:  PuckSort.h
//
//    Description:  
//
//        Created:  06/09/2017 05:11:36 PM
//
//         Author:  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
//
// =====================================================================================

#ifndef  PuckSort_INC
#define  PuckSort_INC

#include "PuckSignal.h"

using namespace PuckSignal;

class PuckSort {
    public:
        PuckSort(){};
        ~PuckSort(){};

        /*! 
         *  \brief Determine if puck has to be discarded or will be kept
         *  \argument [in] signal Signal to process
         *  \return true Puck shall be discarded
         *          false Puck shall be kept
         */
        bool process(PuckType signal);

    private:

};

#endif   // ----- #ifndef PuckSort_INC  ----- 
