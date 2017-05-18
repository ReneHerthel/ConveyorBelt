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

#ifndef TESTHEIGHTMEASUREMENTSTATEMACHINE_H_
#define TESTHEIGHTMEASUREMENTSTATEMACHINE_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestHeightMeasurementStatemachine : public TestCase
{
public:
    /*
     * @brief
     */
	TestHeightMeasurementStatemachine(int id, std::string brief) : TestCase(id, brief) { };

protected:
	/*
	 * @brief The test for the normal Type.
	 */
	TEST(test1);

	/*
	 * @brief The test for the flipped Type.
	 */
	TEST(test2);

	/*
	 * @brief The test for the invalid Type.
	 */
	TEST(test3);

	/*
	 * @brief The test for the Bitcoded 101 type.
	 */
	TEST(test4);

	/*
	 * @brief The test for the Bitcoded 010 type.
	 */
	TEST(test5);

    // Must have.
    TEST_CASE_METHODS
};


#endif /* TESTHEIGHTMEASUREMENTSTATEMACHINE_H_ */
/** @} */
