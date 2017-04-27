/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    height_measurement
 * @{
 *
 * @brief      Service header declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef HEIGHTMEASUREMENTSERVICE_H_
#define HEIGHTMEASUREMENTSERVICE_H_

#define DELTA_VAL (calibrationDataPtr->delta)
#define REF_HEIGHT_VAL (calibrationDataPtr->refHeight)
#define HOLE_HEIGHT_VAL (calibrationDataPtr->holeHeight)
#define SURFACE_HEIGHT_VAL (calibrationDataPtr->surfaceHeight)
#define LOW_HEIGHT_VAL (calibrationDataPtr->lowHeight)
#define HIGH_HEIGHT_VAL (calibrationDataPtr->highHeight)

#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <thread>
#include <iostream>
#include <sys/netmgr.h>
#include <stdint.h>


#include "HeightContext.h"

class HeightMeasurementService {
public:
	struct CalibrationData {
		int16_t delta;
		int16_t refHeight;
		int16_t holeHeight;
		int16_t surfaceHeight;
		int16_t highHeight;
		int16_t lowHeight;
	};

	HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr);
	virtual ~HeightMeasurementService();
private:
	HeightContext stateMachine;
	CalibrationData *calibrationDataPtr;
	void measuringTask(int measuring_chid);
	void stateMachineTask(int receive_chid);

	std::thread measurementThread;
	std::thread stateMachineThread;
};

#endif /* HEIGHTMEASUREMENTSERVICE_H_ */
/** @} */
