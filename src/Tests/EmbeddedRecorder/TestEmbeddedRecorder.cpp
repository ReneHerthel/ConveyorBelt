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

#include "TestEmbeddedRecorder.h"

#include "IEmbeddedRecorder.h"
#include "EmbeddedRecorder.h"

SETUP(TestEmbeddedRecorder) {
    REG_TEST(test1, 1, "TODO");
}

BEFORCE_TC(TestRecordBuffer) {
    // Empty.
    return 1;
}

AFTER_TC(TestRecordBuffer) {
    // Empty.
    return 1;
}

BEFORCE(TestRecordBuffer) {
    // Empty.
    return 1;
}

AFTER(TestRecordBuffer) {
    // Empty.
    return 1;
}

TEST_IMPL(TestRecordBuffer, test1) {
    return TEST_FAILED;
}

/** @} */
