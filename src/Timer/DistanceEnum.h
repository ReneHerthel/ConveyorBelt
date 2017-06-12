/*
 * DistanceEnum.h
 *
 *  Created on: 08.06.2017
 *      Author: aca619
 */

#ifndef DISTANCEENUM_H_
#define DISTANCEENUM_H_

namespace DistanceSpeed{
	enum speed_t{
		FAST,
		SLOW,
		STOP
	};

	/**
	 * Distanced between the exit of one lightbarrier and the entry of another
	 * |				   |
	 * |<----Distance----->|
	 * |				   |
	 * LB				   LB
	 */
	enum lb_distance{
		INLET_TO_HEIGHT,
		HEIGHT_TO_SWITCH,
		SWITCH_TO_OUTLET,
		OUT_TO_IN			///Note that this is an aprox, make delta big
	};
};

#endif /* DISTANCEENUM_H_ */
