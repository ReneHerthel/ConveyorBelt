/*
 * Calibration.h
 *
 *  Created on: 09.06.2017
 *      Author: aca619
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <chrono>;

#define PORTB_ADDR 0x301

using namespace std::chrono;

class Calibration {
public:
	enum sensor_t : uint8_t {
		LB_ENTRY  	   =0b00000001,
		LB_HEIGHT  	   =0b00000010,
		SENSOR_HEIGHT  =0b00000100,
		LB_SWITCH 	   =0b00001000,
		SENSOR_METAL   =0b00010000,
		SWITCH_OPEND   =0b00100000,
		LB_RAMP 	   =0b01000000,
		LB_EXIT		   =0b10000000
	};

	void calibrate(void);

	bool pollLB(sensor_t sensor);

private:
	milliseconds overall;
	milliseconds heightMeasure;
	milliseconds sortingSwitch;
	milliseconds outlet;

	uint32_t sowToFastFactor;
	uint32_t fastToSlowDivisor;
};

#endif /* CALIBRATION_H_ */
