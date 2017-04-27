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
 * @brief      Service function declaration of the HeightMeasurement component
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "HeightMeasurementService.h"
#include "HeightMeasurementHal.h"

HeightMeasurementService::HeightMeasurementService(int receive_chid, int send_chid, CalibrationData *calibrationDataPtr)
: stateMachine(send_chid)
, calibrationDataPtr(calibrationDataPtr)
{
	measurementThread = std::thread(&HeightMeasurementService::measuringTask, this, receive_chid);
	stateMachineThread = std::thread(&HeightMeasurementService::stateMachineTask, this, receive_chid);
}

HeightMeasurementService::~HeightMeasurementService() {

}

void HeightMeasurementService::measuringTask(int receive_chid) {
	int16_t data = 0;
	HeightContext::Signal state = HeightContext::START;
	int16_t maxHeight = 0;
	int16_t minHeight = 0;

	HeightMeasurementHal hal;
	int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);
	if(coid < 0) {
		// todo error handling
	}
	while(1) {
		hal.read(data);

		maxHeight = data + DELTA_VAL;
		minHeight = data - DELTA_VAL;

		if(state != HeightContext::REF_HEIGHT && (maxHeight < REF_HEIGHT_VAL && minHeight > REF_HEIGHT_VAL)) {

		}
		else if (state != HeightContext::HOLE_HEIGHT && (maxHeight < HOLE_HEIGHT_VAL && minHeight > HOLE_HEIGHT_VAL)) {

		}
		else if (state != HeightContext::SURFACE_HEIGHT && (maxHeight < SURFACE_HEIGHT_VAL && minHeight > SURFACE_HEIGHT_VAL)) {

		}
		else if (state != HeightContext::LOW_HEIGHT && (maxHeight < LOW_HEIGHT_VAL && minHeight > LOW_HEIGHT_VAL)) {

		}
		else if (state != HeightContext::HIGH_HEIGHT && (maxHeight < HIGH_HEIGHT_VAL && minHeight > HIGH_HEIGHT_VAL)) {

		}
	}
}

void HeightMeasurementService::stateMachineTask(int receive_chid) {
	int coid = ConnectAttach_r(ND_LOCAL_NODE, 0, receive_chid, 0, 0);
	if(coid < 0) {
		// todo error handling
	}

	struct _pulse pulse;
	while(1) {
		int err = MsgReceivePulse_r(receive_chid, &pulse, sizeof(_pulse), NULL);
		if(err) {
			// todo error handling
		}

		stateMachine.process((HeightContext::Signal) pulse.value.sival_int);
	}
}

/** @} */
