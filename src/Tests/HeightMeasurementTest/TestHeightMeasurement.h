/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    wrapper
 * @{
 *
 * @brief      Test Header of the PulseMessageWrapper.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef TESTHEIGHTMEASUREMENT_H_
#define TESTHEIGHTMEASUREMENT_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestHeightMeasurement : public TestCase
{
public:
    /*
     * @brief
     */
	  TestHeightMeasurement(int id, std::string brief) : TestCase(id, brief) { };

protected:
	  /*
	   * @brief The test for the normal Type.
	   */
	  TEST(ManualCalibration);

    // Must have.
    TEST_CASE_METHODS
};

#endif /* TESTHEIGHTMEASUREMENTSTATEMACHINE_H_ */
/** @} */
