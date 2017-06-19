/*
 * Calibration.h
 *
 *  Created on: 09.06.2017
 *      Author: aca619
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include <chrono>
#include "DistanceEnum.h"
#include "SortingSwitchService.h"
#include "HeightMeasurementService.h"
#include "Signals.h"

#define PORTB_ADDR 0x301

#define SURFACE 	0.6203931
#define HOLE		0.8771498
#define LOGICAL_1	0.7257900
#define LOGICAL_0	0.6584766
#define INVALID		0.6862400
#define DELTA		35

#define CALC_ABS_HEIGHT(val, perc) ((int16_t)((double)val*perc));

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

	/**
	 * Calibrate the light barrier distances
	 */
	void calibrate(int mainChid);

	bool pollLB(sensor_t sensor);

	/**
	 * Get the Instance of the Calibration Sigleton
	 */
	static Calibration& getInstance();

	/**
	 * Get the Calibration data for a distance between two Lightbarriers
	 * @param distance The distance of which the calibration is needed
	 * @param speed The speed the belt is running with
	 */
	uint32_t getCalibration(DistanceSpeed::lb_distance distance, DistanceSpeed::speed_t speed);

	void calibrateHeighMeasurement(void);

	void manualCalibration(uint32_t hf, uint32_t hs, uint32_t sf, uint32_t ss, uint32_t of, uint32_t os, uint32_t ovf, uint32_t ovs);

	HeightMeasurementService::CalibrationData getHmCalibration(void);

	double getFastToSlow(void);

	double getSlowToFast(void);

	void print(void);

private:
	Calibration();
	~Calibration();

	std::chrono::milliseconds overall[2];
	std::chrono::milliseconds heightMeasure[2];
	std::chrono::milliseconds sortingSwitch[2];
	std::chrono::milliseconds outlet[2];
	std::chrono::milliseconds inlet[2];
	std::chrono::milliseconds inSwitch[2];

	double fastToSlowFactor;
	double slowToFastFactor;

	HeightMeasurementService::CalibrationData hmCal; ///Calibration Data for height measurement
};

#endif /* CALIBRATION_H_ */
