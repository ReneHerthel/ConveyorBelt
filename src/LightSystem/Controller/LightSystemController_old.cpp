// =====================================================================================
// LightSystemController.cpp : Controller sets Lights according to
// warning level
// 
//    Copyright (c) 2017 Stephan Jaenecke <stephan.jaenecke@haw-hamburg.de>
// =====================================================================================

#include "LightSystemController.h"
#include "ITimer.h"
LightSystemController :: LightSystemController(int chid
		//, ITimer* timer
		, BLightSystem* boundary)
	: chid(chid)
	, timer(timer)
	, boundary(boundary)
{}


int LightSystemController::task(){
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}
	int state = ALL_ALWAYS_OFF;
	int msg;
	while(1){
		// Wait for pulse message
		// Process message



		switch(state){
			case ALL_ALWAYS_OFF:
				switch(msg){
					case OPERATING and ALWAYS_ON:
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case WARNING and SLOW_BLINKING :
						state = YELLOW_ON;
						lightOn(YELLOW);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					default:

				}
				break;
			case GREEN_ALWAYS_ON:
				switch(msg){
					case WARNING and SLOW_BLINKING :
						lightOff(GREEN);
						state = YELLOW_ON;
						lightOn(YELLOW);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						lightOff(GREEN);
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						lightOff(GREEN);
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						lightOff(GREEN);
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					case NOT_OPERATING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						lightOff(GREEN);
						state = ALL_ALWAYS_OFF;
						break;
					default:
							//todo error handling
				}
				break;
			case YELLOW_ON    :
				switch(msg){
					case OPERATING and ALWAYS_ON:
					 	lightOff(YELLOW);
					 	state = GREEN_ALWAYS_ON;
					 	lightOn(GREEN);
					 	break;
					case TIMER_OFF and MSG_YELLOW :
						lightOff(YELLOW);
						state = YELLOW_OFF;
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						lightOff(YELLOW);
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						lightOff(YELLOW);
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						lightOff(YELLOW);
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						lightOff(YELLOW);
						state = ALL_ALWAYS_OFF;
						break;
					default:
							//todo error handling
				}
				break;
			case YELLOW_OFF   :
				switch(msg){
					case OPERATING and ALWAYS_ON:
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case TIMER_OFF and MSG_YELLOW :
						state = YELLOW_ON;
						lightON(YELLOW);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						state = ALL_ALWAYS_OFF;
						break;
					default:
							//todo error handling
				}
				break;
			case RED_ALWAYS_ON:
				switch(msg){
					case OPERATING and ALWAYS_ON:
						lightOff(RED);
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						lightOff(RED);				//cause of exit action
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case WARNING and SLOW_BLINKING:
						lightOff(RED);
						state = YELLOW_ON;
						lightOn(YELLOW);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						lightOff(RED);
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						lightOff(RED);
						state = ALL_ALWAYS_OFF;
						break;
					default:
							//todo error handling
				}
				break;
			case RED_FAST_ON  :
				switch(msg){
					case OPERATING and ALWAYS_ON:
						lightOff(RED);
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						lightOff(RED);				//cause of exit action
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case WARNING and SLOW_BLINKING:
						lightOff(RED);
						state = YELLOW_ON;
						lightOn(YELLOW);
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						lightOff(RED);
						state = RED_ALWAYS_ON;
						lightOn(RED);

						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						lightOff(RED);
						state = ALL_ALWAYS_OFF;
						break;
					case TIMER_OFF and RED_FAST :
						lightOff(RED);
						state = RED_FAST_OFF;
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					default:
							//todo error handling
				}
				break;
			case RED_FAST_OFF :
				switch(msg){
					case OPERATING and ALWAYS_ON:
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case ERROR_GONE_UNACKNOWLEDGED and SLOW_BLINKING:
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case WARNING and SLOW_BLINKING:
						state = YELLOW_ON;
						lightOn(YELLOW);
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						state = ALL_ALWAYS_OFF;
						break;
					case TIMER_OFF and MSG_RED_FAST :
						state = RED_FAST_ON;
						lightOn(RED);
						timer.setAlarm(FAST_BLINKING);	//todo replace by clever message
						break;
					default:
							//todo error handling
				}
				break;
			case RED_SLOW_ON  :
				switch(msg){
					case OPERATING and ALWAYS_ON:
						lightOff(RED);
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						lightOff(RED);				//cause of exit action
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case WARNING and SLOW_BLINKING:
						lightOff(RED);
						state = YELLOW_ON;
						lightOn(YELLOW);
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						lightOff(RED);
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						lightOff(RED);
						state = ALL_ALWAYS_OFF;
						break;
					case TIMER_OFF and MSG_RED_SLOW :
						lightOff(RED);
						state = RED_SLOW_OFF;
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					default:
							//todo error handling
				}
				break;
			case RED_SLOW_OFF :
				switch(msg){
					case OPERATING and ALWAYS_ON:
						state = GREEN_ALWAYS_ON;
						lightOn(GREEN);
						break;
					case ERROR_OCCURED and FAST_BLINKING:
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					case WARNING and SLOW_BLINKING:
						state = YELLOW_ON;
						lightOn(YELLOW);
						break;
					case ERROR_ACKNOWLEDGED and ALWAYS_ON:
						state = RED_ALWAYS_ON;
						lightOn(RED);
						break;
					case CLEAR_WARNING and ALWAYS_OFF or CLEAR_ALL and ALWAYS_OFF:
						state = ALL_ALWAYS_OFF;
						break;
					case TIMER_OFF and MSG_RED_SLOW :
						state = RED_SLOW_ON;
						lightOn(RED);
						timer.setAlarm(SLOW_BLINKING);	//todo replace by clever message
						break;
					default:
							//todo error handling
				}
				break;
			default:
				//todo error handling
		}
		}

	}

	// Set lamp

	// Start timer

}
