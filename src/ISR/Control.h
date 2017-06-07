/*
 * Name        : Control.h
 * Author      : abt674
 * Version     : 0.7
 * Copyright   : none
 */

#ifndef Control_H_
#define Control_H_


//Lightbarriers and Sensor
#define LightBarrier_ENTRY  		0b0000000000000001
#define LightBarrier_HEIGHT  		0b0000000000000010
#define SENSOR_HEIGHT 	            0b0000000000000100
#define LightBarrier_SWITCH 		0b0000000000001000
#define SENSOR_METAL 	            0b0000000000010000
#define SWITCH_OPEN					0b0000000000100000
#define LightBarrier_RAMP 		    0b0000000001000000
#define LightBarrier_EXIT		 	0b0000000010000000

//Buttons
#define BUTTON_START	            0b0001000000000000
#define BUTTON_STOP			  	  	0b0010000000000000
#define BUTTON_RESET				0b0100000000000000
#define BUTTON_ESTOP				0b1000000000000000


class Control {

public:
	Control();
	virtual ~Control();

	void LightBarrier_ENTRY_IN();
	void LightBarrier_ENTRY_OUT();

	void LightBarrier_HEIGHT_IN();
	void LightBarrier_HEIGHT_OUT();

	void LightBarrier_SWITCH_IN();
	void LightBarrier_SWITCH_OUT();

	void LightBarrier_RAMP_IN();
	void LightBarrier_RAMP_OUT();

	void LightBarrier_EXIT_IN();
	void LightBarrier_EXIT_OUT();

	void HEIGHT();
	void METAL();
	void SWITCH();

	void B_Start();
	void B_STOP();
	void B_EStop();
	void B_Reset();


};

#endif /* Control_H_ */
