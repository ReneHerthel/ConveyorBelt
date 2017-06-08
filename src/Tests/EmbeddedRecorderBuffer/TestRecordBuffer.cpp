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

#include "TestRecordBuffer.h"

#include "IRecordBuffer.h"
#include "RecordBuffer.h"

SETUP(TestRecordBuffer) {
    REG_TEST(test1, 1, "Fill the buffer complete");
    return 1;
}

BEFORE_TC(TestRecordBuffer) {
    // Empty.
	return 1;
}

AFTER_TC(TestRecordBuffer) {
    // Empty.
	return 1;
}

BEFORE(TestRecordBuffer) {
    // Empty.
	return 1;
}

AFTER(TestRecordBuffer) {
    // Empty.
	return 1;
}

TEST_IMPL(TestRecordBuffer, test1) {
    rec::IRecordBuffer * buffer = new rec::RecordBuffer();

    rec::record_t r;

    int size = 65536;

    // Make sure the defined buffersize of the buffer is 128.
    for (int i = 0; i < size; i++) {
        r.code = i;
        r.value = i;
        r.timestamp = i;
        buffer->write(r);
    }

    for (int i = 0; i < size; i++) {
        buffer->read(&r);
    }

    if (buffer->read(&r) < 0) {
        return TEST_PASSED;
    }

    return TEST_FAILED;
}

/** @} */
