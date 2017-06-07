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

#include "IRecordBuffer.h"
#include "RecordBuffer.h"

SETUP(TestRingbuffer) {
    REG_TEST(test1, 1, "Fill the buffer complete");

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
    IRecordBuffer * buffer = new RecordBuffer();

    record_t * r;

    // Make sure the defined buffersize of the buffer is 128.
    for (int i = 0; i < 128; i++) {
        r.code = i;
        r.value = i;
        r.timeStamp = i;
        buffer->write(r);
    }

    for (int i = 0; i < 128; i++) {
        buffer->read(r);
    }

    if (buffer->read(r) == -2) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
