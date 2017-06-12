// =====================================================================================
//
//       Filename:  PuckSortContext.h
//
//    Description:  
//
//        Created:  06/09/2017 05:11:36 PM
//
//         Author:  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
//
// =====================================================================================

#ifndef  PuckSortContext_INC
#define  PuckSortContext_INC

#include "PuckSignal.h"

using namespace PuckSignal;

class PuckSortContext {
    public:
        PuckSortContext(){};
        ~PuckSortContext(){};

        /*! 
         *  \brief Determine if puck has to be discarded or will be kept
         *  \argument [in] signal Signal to process
         *  \return true Puck shall be discarded
         *          false Puck shall be kept
         */
        bool process(PuckType signal);

    struct PuckSort {
        /* FIXME: Adapt signal names to puck naming conventions */
        virtual void bitCode1();
        virtual void bitCode2();
        virtual void bitCode4();
        virtual void bitCode5();
        virtual void flipped();
        virtual void lowHeight();
        virtual void holeWithoutMetal();
        virtual void holeWithMetal();
    }

    struct Start: public PuckSort {
    };
    /* FIXME: Adapt state names to puck naming conventions */
    struct GotHoleUpWoMetal: public PuckSort {
    };
    struct GotTwoHoleUpWoMetal: public PuckSort {
    };
    struct GotHoleUpMetal: public PuckSort {
    };
};

#endif   // ----- #ifndef PuckSortContext_INC  ----- 
