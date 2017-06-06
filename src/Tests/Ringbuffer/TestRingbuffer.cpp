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

#include "TestRingbuffer.h"

SETUP(TestRingbuffer) {
    REG_TEST(test1, 1, "Fill the buffer complete");
    REG_TEST(test2, 2, "Empty the buffer complete");

    return 1;
}

BEFORE_TC(TestRingbuffer) {
    // Empty.
	return 1;
}

AFTER_TC(TestRingbuffer) {
    // Empty.
	return 1;
}

BEFORE(TestRingbuffer) {
    // Empty.
	return 1;
}

AFTER(TestRingbuffer) {
    // Empty.
	return 1;
}

TEST_IMPL(TestRingbuffer, test1) {
    return TEST_FAILED;
}

TEST_IMPL(TestRingbuffer, test2) {
    return TEST_FAILED;
}

/** @} */
