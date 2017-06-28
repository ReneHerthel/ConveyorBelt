/*!
 *    \file  PuckSortContext.h
 *   \brief  Declares the structures for the PuckSort state machine
 *
 *  \author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *  \internal
 *       Created:  06/09/2017
 * Last modified:  06/21/2017
 *     Copyright:  Copyright (c) 2017 Stephan Jänecke licensed under the
 *     MIT License
 */

#ifndef  PuckSortContext_INC
#define  PuckSortContext_INC

#include "Logger.h"
#include "LogScope.h"
#include "PuckSignal.h"
#include "SerialProtocoll.h"

using namespace PuckSignal;

/* FIXME: Adapt state names to puck naming conventions */
/*!
 *  \brief  Defines the context of the Superstate PuckSort and its
 *  specialized states.
 */
class PuckSortContext {
    public:
        PuckSortContext();
        ~PuckSortContext(){};

        /*! 
         *  \brief Determine if puck has to be discarded or will be kept
         *  \argument [in] signal Puck to process
         *  \return true Puck shall be discarded
         *          false Puck shall be kept
         */
        bool process(PuckType signal);
        /*! 
         *  \brief Process slide full message from local puck
         *  \argument [in] message Message to process
         */
        void process(PuckReturn message);
        /*! 
         *  \brief Process slide full message from remote puck
         *  \argument [in] message Message to process
         */
        void process(Serial_n::ser_proto_msg message);
        /*!
         *  \brief Check if all slides are full
         *  \return true All slides are full
         *  		false Either one of the slides is full or none
         */
        bool areBothSlidesFull(void);
        /*!
         *  \brief Resets the slide conditionals
         */
        void resetSlides(void);
    /*!
     *  \brief  Define standard transitions
     *
     *  Transitions are taken when transitions are not defined in
     *  specialized states.
     */
    struct PuckSort {
        /*!
         *  \brief  Standard transition for binary 1 encoded puck
         *
         *  Puck will be discarded on machine 0 provided the slide is
         *  not full.
         */
        virtual void bitCode1();
        /*!
         *  \brief  Standard transition for binary 2 encoded puck
         *
         *  Puck will be discarded on machine 1 provided the slide is
         *  not full.
         */
        virtual void bitCode2();
        /*!
         *  \brief  Standard transition for binary 4 encoded puck
         *
         *  Puck will be discarded on machine 1 provided the slide is
         *  not full.
         */
        virtual void bitCode4();
        /*!
         *  \brief  Standard transition for binary 5 encoded puck
         *
         *  Puck will be discarded on machine 0 provided the slide is
         *  not full.
         */
        virtual void bitCode5();
        /*!
         *  \brief  Standard transition for flipped puck
         *
         *  Puck will be discarded immediately provided the slide on the
         *  current machine is not full.
         */
        virtual void flipped();
        /*!
         *  \brief  Standard transition for puck without metal
         *
         *  Puck is out of order and will be discarded on machine 1
         *  provided the slide is not full.
         */
        virtual void holeWithoutMetal();
        /*!
         *  \brief  Standard transition for puck with metal
         *
         *  Puck is out of order and will be discarded on machine 1
         *  provided the slide is not full.
         */
        virtual void holeWithMetal();
        /*!
         *  \brief  Standard transition for invalid puck
         *
         *  Puck will be discarded on machine 0 provided the slide is
         *  not full.
         */
        virtual void invalid();

        bool slide0IsEmpty; /*!< \brief Set if slide 0 is empty */
        bool slide1IsEmpty; /*!< \brief Set if slide 1 is empty */
        bool isOnMachine0; /*!< \brief Set if PuckSort is running on machine 0 */
        bool isOnMachine1; /*!< \brief Set if PuckSort is running on machine 1 */
        bool returnValue; /*!< \brief Contains result of taken transition */

		/*!
		 *  \brief  Print current state of state machine conditionals
		 */
		void logConditionals(void);
    } *statePtr;

    /*!
     *  \brief  No pucks from sequence
     *
     *  Wait for puck without metal.
     */
    struct Start: public PuckSort {
        /*!
         *  \brief  Transition for puck without metal from Start
         *
         *  Puck is in order and will be passed on to machine 1.
         */
        virtual void holeWithoutMetal();
    } startState;
    /*!
     *  \brief  Got one puck without metal
     *
     *  Wait for puck without metal.
     */
    struct GotHoleUpWoMetal: public PuckSort {
        /*!
         *  \brief  Transition for puck without metal from
         *  GotHoleUpWoMetal
         *
         *  Puck is in order and will be passed on to machine 1.
         */
        virtual void holeWithoutMetal();
    };
    /*!
     *  \brief  Got two pucks without metal
     *
     *  Wait for puck with metal.
     */
    struct GotTwoHoleUpWoMetal: public PuckSort {
        /*!
         *  \brief  Transition for puck with metal from
         *  GotTwoHoleUpWoMetal
         *
         *  Puck is in order and will be passed on to machine 1.
         */
        virtual void holeWithMetal();
    };
    /*!
     *  \brief  Got two pucks without metal and one puck with metal
     *
     *  All pucks from the sequence have been detected in order. No
     *  further state transitions.
     */
    struct GotHoleUpMetal: public PuckSort {
    };
};

#endif   // ----- #ifndef PuckSortContext_INC  ----- 
