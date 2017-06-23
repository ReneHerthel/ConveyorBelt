/*
 * Copyright (C) 2017 Rene Herthel
 * Copyright (C) 2017 Jonas Fuhrmann
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    height_context
  * @{
  *
  * @brief      state machine for the height measurement.
  *
  * @author     Jonas Fuhrmann <jonas.fuhrmann@haw-hamburg.de>
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef HEIGHTCONTEXT_H_
#define HEIGHTCONTEXT_H_

#include "HeightSignal.h"
#include "HeightMeasurementController.h"

#include <functional>
#include <vector>

/*
 * @brief Defines the maximum and minimum size of the pattern array.
 * @{
 */
#define MAX_BIT_SIZE 3
#define MIN_BIT_SIZE 3
/** @} */

class HeightMeasurementController;

using namespace HeightMeasurement;

class HeightContext {
private:
    /*
     * @brief The super state from where all states will be inherit.
     */
    struct State {
        virtual void invalid();
        virtual void start();
        virtual void stop();
        virtual void holeHeight();
        virtual void surfaceHeight();
        virtual void refHeight();
        virtual void patternRead();
        virtual void lowHeight();
        virtual void highHeight();
        virtual void entry();

        void send(int coid, signal_t signal);
        unsigned int index;
        int coid;  // The channel, where the statemachine will send to.
        HeightMeasurementController *service;  // A pointer to the service class.
    } *statePtr;

    /*
     * @brief The Idle state of the state machine.
     *
     * @description This state will stop the measuring and the timer in its
     *              entry function.
     *              The next transition (START) goes to the Measuring state.
     */
    struct Idle : public State {
    	Idle();
        void entry();
        void start();
    };

    /*
     * @brief The Measuring state of the state machine.
     *
     * @description This state will start the measuring and the timer in its
     *              entry function.
     *              The next transition (HOLE_HEIGHT) goes to the NORMAL state.
     */
    struct Measuring : public State {
        void entry();
        void invalid();
        void surfaceHeight();
        void holeHeight();
        void lowHeight();
        void highHeight();
    };

    /*
     * @brief The Normal state of the state machine.
     *
     * @description This state indicates, that there is a valid puck.
     *              The next transition (SURFACE_HEIGHT) goes to the SURFACE state.
     */
    struct Normal : public State {
        void entry();
        void surfaceHeight();
    };

    /*
     * @brief The Surface state of the state machine.
     *
     * @description This state indicates that the Measurement-Thread measures
     *              from the Top of the puck.
     *              The next transition (REF_HEIGHT) goes to the IDLE state.
     */
    struct Surface : public State {
        void entry();
        void refHeight();
    };

    /*
     * @brief The BitOrFlipped state of the state machine.
     *
     * @description This state indicates that the puck is bit-coded or flipped.
     *              It contains an array, which helds the bit-pattern of the
     *              bit-coded puck.
     *              It contains sub-states, which are represented as a hierachical
     *              state machine.
     *              The next state is the TOP state of the hierachical state machine.
     */
    struct BitOrFlipped : public State {
        bool pattern[MAX_BIT_SIZE];

        void entry();
        void patternRead();
    };

    /*
     * @brief The Top state of the hierachical state machine of BitOrFlipped.
     *
     * @description This state indicates that the measurer is on the top
     *              of the puck.
     *              It can reach five states, depending on the signal, which the
     *              measurement-Thread will send:
     *              LOW_HEIGHT, when the measurement reads a low-bit.
     *              SURFACE_HEIGHT, when the measurement is on the top again.
     *              HIGH_HEIGHT, when the measurement reads a high-bit.
     *              REF_HEIGHT, when the measurement reads directly from the belt.
     *              The REF_HEIGHT signal indicates that the puck is either
     *              FLIPPED (when the index is 0, so no bit was read) or a pattern
     *              was successfully read (goes to BIT_CODED).
     */
    struct Top : public BitOrFlipped {
        void entry();
        void refHeight();
        void lowHeight();
        void highHeight();
    };

    /*
     * @brief The High state of the hierachical state machine of BitOrFlipped.
     *
     * @description This state indicates that the measurement thread has read a
     *              high-bit. It places the bit into the pattern array at the
     *              position of the index.
     *              The next transition (SURFACE_HEIGHT) goes to the TOP state.
     */
    struct High : public BitOrFlipped {
    	High();
    	void entry();
        void surfaceHeight();
    };

    /*
     * @brief The Low state of the hierachical state machine of BitOrFlipped.
     *
     * @description This state indicates that the measurement thread has read a
     *              low-bit. It places the bit into the pattern array at the
     *              position of the index.
     *              The next transition (SURFACE_HEIGHT) goes to the TOP state.
     */
    struct Low : public BitOrFlipped {
    	Low();
    	void entry();
        void surfaceHeight();
    };

    /*
     * @brief The Flipped state of the hierachical state machine of BitOrFlipped.
     *
     * @description This state indicates that the puck is flipped.
     *              The index was zero, when the measurement has read REF_HEIGHT.
     *              So the only thing the measurement has read was the surface
     *              of the puck, so no bits are in the pattern.
     *              The next transition (PATTERN_READ) goes out of the hierachical
     *              state machine into the IDLE state.
     */
    struct Flipped : public BitOrFlipped {
        void entry();
    };

    /*
     * @brief The BitCoded state of the hierachical state machine of BitOrFlipped.
     *
     * @description This state indicates that a bit-code has been read from the puck.
     *              The index is greater than zero and a pattern is in the array.
     *              Then it will send in the entry() function the pattern via
     *              msgSend().
     *              The next transition (PATTERN_READ) goes out of the hierachical
     *              state machine into the IDLE state.
     */
    struct BitCoded : public BitOrFlipped {
        void entry();
    };

    /*
     * @brief A reference to the current state of the state machine.
     */
    State state;

    /*
     * @brief A pointer to the reference class to start & stop the measuring.
     */
    HeightMeasurementController *service;

    /*
     * @brief The connection ID of the send channel ID.
     */
    int coid;

public:
    /*
     * @brief The constructor with the ID of the send channel.
     */
    HeightContext(int send_chid, HeightMeasurementController *service);

    /*
     * @brief Inteprets the given signal and invoke the corresponding function.
     * @param [signal] The signal for the next transition.
     */
    void process(HeightMeasurement::Signal signal);
};

#endif /* HEIGHTCONTEXT_H_ */
/** @} */
