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
 * @brief      Test Function of the Ringbuffer.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_TESTS_RINGBUFFER_TESTRINGBUFFER_H_
#define SRC_TESTS_RINGBUFFER_TESTRINGBUFFER_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestRingbuffer : public TestCase
{
public:
	/*
	 * @brief TODO
	 */
	TestRingbuffer(int id, std::string brief) : TestCase(id, brief) { };

protected:
    /*
     * @brief TODO
     */
    TEST(test1);

    /*
     * @brief TODO
     */
    TEST(test2);

    // Must have.
    TEST_CASE_METHODS
};

#endif /* SRC_TESTS_RINGBUFFER_TESTRINGBUFFER_H_ */
/** @} */
