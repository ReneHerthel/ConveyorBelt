/*!
 * @file PuckSortContext.h
 * @brief
 *
 * @author Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 * @internal
 * Created 06/09/2017 05:11:22 PM
 * Copyright  Copyright (c) 2017 Stephan Jänecke
 *
 */

#ifndef  PuckSortContext_INC
#define  PuckSortContext_INC

#include "PuckSignal.h"

#define MACHINE 0
#define FIFO_SORT 0

using namespace PuckSignal;

class PuckSortContext {
    public:
        PuckSortContext();
        ~PuckSortContext(){};

        /*! 
         *  \brief Determine if puck has to be discarded or will be kept
         *  \argument [in] signal Signal to process
         *  \return true Puck shall be discarded
         *          false Puck shall be kept
         */
        bool process(PuckType signal);

        bool rampe1IsEmpty;
        bool rampe2IsEmpty;
        bool isOnMachine1;
        bool isOnMachine2;

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
    };

    struct Start: public PuckSort {
        /* FIXME: Adapt state names to puck naming conventions */
        virtual void holeWithoutMetal();
    };
    struct GotHoleUpWoMetal: public PuckSort {
        /* FIXME: Adapt signal names to puck naming conventions */
        virtual void holeWithoutMetal();
    };
    struct GotTwoHoleUpWoMetal: public PuckSort {
        /* FIXME: Adapt signal names to puck naming conventions */
        virtual void holeWithMetal();
    };
    struct GotHoleUpMetal: public PuckSort {
    };
};

#endif   // ----- #ifndef PuckSortContext_INC  ----- 
