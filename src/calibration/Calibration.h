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
#include "HeightMeasurementController.h"
#include "PulseMessageReceiverService.h"
#include "Signals.h"
#include <string>

#define PORTB_ADDR 0x301

// in millimeters
#define SURFACE 	25.0
#define HOLE		 7.3
#define LOGICAL_1	18.5
#define LOGICAL_0	21.5
#define INVALID		20.75

#define DELTA		35

#define CALC_ABS_HEIGHT(val, perc) ((int16_t)((double)val*perc));

#define INLET_CAL_SLOW 1550 //Measured 1.8, for seftys sake make it slower
#define INLET_CAL_FAST 500  //Unmeasured, educated gues

#define SLIDE_TIMER_FAST 5000 //5 seconds, (un)educated guess
#define SLIDE_TIMER_SLOW 10000 //5 seconds, (un)educated guess

using namespace std::chrono;

class Calibration {
public:
	enum sensor_t : uint8_t {
		LB_ENTRY  	   =0b00000001,
		LB_HEIGHT  	   =0b00000010,
		SSENSOR_HEIGHT  =0b00000100,
		LB_SWITCH 	   =0b00001000,
		SSSENSOR_METAL   =0b00010000,
		SSWITCH_OPEND   =0b00100000,
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

	/**
	 * Save lb calibration to the disk
	 */
	bool saveToDisk(std::string path);

	bool loadFromDisk(std::string path);

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

	void manualCalibration(uint32_t hf, uint32_t hs, uint32_t sf, uint32_t ss, uint32_t of, uint32_t os, uint32_t ovf, uint32_t ovs);

	HeightMeasurementController::CalibrationData getHmCalibration(void);

	double getFastToSlow(void);

	double getSlowToFast(void);

	void print(void);

private:
	Calibration();
	~Calibration();

	void calibrateHeighMeasurement(rcv::PulseMessageReceiverService *pmr);

	uint16_t getAvg();

	//v slow and fast, distances between lightbarriers (lb) in ms, lb_out to lb_in time v//
	std::chrono::milliseconds overall[2]; 		///Overall distance from inlet to outlet
	std::chrono::milliseconds heightMeasure[2];	///Distance from inlet to height Measurement lb
	std::chrono::milliseconds sortingSwitch[2];	///From height Measurement to the switch
	std::chrono::milliseconds outlet[2];		///from switch to outlet
	std::chrono::milliseconds inlet[2];			///from outlet to inlet on machine 2
	std::chrono::milliseconds inSwitch[2];		///Unused
	std::chrono::milliseconds slide[2]; 		///Slide timer

	double fastToSlowFactor;
	double slowToFastFactor;

	HeightMeasurementController::CalibrationData hmCal; ///Calibration Data for height measurement
};

#endif /* CALIBRATION_H_ */
