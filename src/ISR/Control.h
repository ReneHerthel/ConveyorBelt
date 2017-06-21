/*
 * Name        : Control.h
 * Author      : abt674
 * Version     : 0.7
 * Copyright   : none
 */

#ifndef Control_H_
#define Control_H_

#include "PulseMessageReceiverService.h"
#include "PulseMessageSenderService.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include "HWaccess.h"
#include "Signals.h"

#include <iostream>
#include <chrono>

//Lightbarriers and Sensor
#define LightBarrier_ENTRY       0b0000000000000001
#define LightBarrier_HEIGHT      0b0000000000000010
#define SENSOR_HEIGHT            0b0000000000000100
#define LightBarrier_SWITCH      0b0000000000001000
#define SENSOR_METAL             0b0000000000010000
#define SWITCH_OPEND             0b0000000000100000
#define LightBarrier_RAMP        0b0000000001000000
#define LightBarrier_EXIT        0b0000000010000000
//Buttons
#define BUTTONSTART              0b0001000000000000
#define BUTTONSTOP               0b0010000000000000
#define BUTTONRESET              0b0100000000000000
#define BUTTONESTOP              0b1000000000000000

#define SWITCH_ISR_DENY_TIME	0.001
	using namespace rcv;

class Control {
public:
    /*
     * @brief Constructor with a channel ID.
     *
     * @param [chid] The channel ID, where this object will make a connection to.
     */
    Control();
    Control(const int chid);

    virtual ~Control();
    void lightBarrier_ENTRY_IN();
    void lightBarrier_ENTRY_OUT();

    void lightBarrier_HEIGHT_IN();
    void lightBarrier_HEIGHT_OUT();

    void lightBarrier_SWITCH_IN();
    void lightBarrier_SWITCH_OUT();

    void lightBarrier_RAMP_IN();
    void lightBarrier_RAMP_OUT();

    void lightBarrier_EXIT_IN();
    void lightBarrier_EXIT_OUT();

    void height();
    void metal();
    void switchopen();
    void switchclosed();

    void b_Start();
    void b_STOP();
    void b_EStop();
    void b_Reset();
private:
    /*
     * @brief The channel ID, where this object will make a connection to.
     */
    int chid_;
    PulseMessageSenderService * sender;
	std::chrono::time_point<std::chrono::system_clock> oldTimestamp;
};

#endif /* Control_H_ */
