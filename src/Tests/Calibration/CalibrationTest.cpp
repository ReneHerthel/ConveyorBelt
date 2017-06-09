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

SETUP(CalibrationTest){
	REG_TEST(Calibrate, 1, "Just Create some distance trackers an let them run (no changes on the way)");
};

BEFORE_TC(CalibrationTest){return 1;}

AFTER_TC(CalibrationTest){return 1;}

BEFORE(CalibrationTest){return 1;}

AFTER(CalibrationTest){return 1;}

TEST_IMPL(CalibrationTest, Calibrate){
	Calibration cal;
	cal.calibrate();
}



