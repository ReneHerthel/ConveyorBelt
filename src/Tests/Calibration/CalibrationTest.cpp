//
// Created by Silt on 23.04.2017.
//

#include "CalibrationTest.h"
#include "Calibration.h"
#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "logger.h"
#include "PulseMessageReceiverService.h"
#include <thread>
#include "ISR.h"
#include "Control.h"

SETUP(CalibrationTest){
	REG_TEST(Calibrate, 1, "Just Create some distance trackers an let them run (no changes on the way)");
};

BEFORE_TC(CalibrationTest){return 1;}

AFTER_TC(CalibrationTest){return 1;}

BEFORE(CalibrationTest){return 1;}

AFTER(CalibrationTest){return 1;}

TEST_IMPL(CalibrationTest, Calibrate){
	rcv::PulseMessageReceiverService pmr;
	int chid = pmr.newChannel();

	Control control(chid);
	ISR isr(&control);
	std::thread isr_thread(ref(isr));

	Calibration& cal = Calibration::getInstance();
	//cal.calibrateHeighMeasurement();

	cal.calibrate(chid);

	HeightMeasurementController::CalibrationData hmCal = cal.getHmCalibration();
	std::cout 	<< "Surface Height (Ref): " << hmCal.refHeight << "\nSurface: " << hmCal.surfaceHeight << "\nHole: " << hmCal.holeHeight
				<< "\nlogical1: " <<  hmCal.highHeight << "\nlogical0: " << hmCal.lowHeight << "\ninvalid: "  << hmCal.invalidHeight << "\ndelta: " << hmCal.delta << "\n";
	std::cout.flush();

	cal.saveToDisk("/Calibration.dat");
	cal.print();
	cal.loadFromDisk("/Calibration.dat");

	hmCal = cal.getHmCalibration();
	std::cout 	<< "Surface Height (Ref): " << hmCal.refHeight << "\nSurface: " << hmCal.surfaceHeight << "\nHole: " << hmCal.holeHeight
				<< "\nlogical1: " <<  hmCal.highHeight << "\nlogical0: " << hmCal.lowHeight << "\ninvalid: "  << hmCal.invalidHeight << "\ndelta: " << hmCal.delta << "\n";
	std::cout.flush();

}



