/*
 * Calibration.h
 *
 *  Created on: 09.06.2017
 *      Author: aca619
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <chrono>;
#include "DistanceEnum.h"

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

	/**
	 * Calibrate the light barrier distances
	 */
	void calibrate(void);

	bool pollLB(sensor_t sensor);

	/**
	 * Get the Instance of the Calibration Sigleton
	 */
	Calibration& getInstance();

	/**
	 * Get the Calibration data for a distance between two Lightbarriers
	 * @param distance The distance of which the calibration is needed
	 * @param speed The speed the belt is running with
	 */
	uint32_t getCalibration(DistanceSpeed::lb_distance distance, DistanceSpeed::speed_t speed);

private:
	Calibration();
	~Calibration();

	milliseconds overall[2];
	milliseconds heightMeasure[2];
	milliseconds sortingSwitch[2];
	milliseconds outlet[2];
	milliseconds inlet[2];

	double slowToFastFactor;
	double fastToSlowDivisor;
};

#endif /* CALIBRATION_H_ */
