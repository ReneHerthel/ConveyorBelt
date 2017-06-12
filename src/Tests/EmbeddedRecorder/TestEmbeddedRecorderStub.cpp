/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    TestEmbeddedRecorderStub
 * @{
 *
 * @brief      The stub object of the EmbeddedRecorder.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestEmbeddedRecorderStub.h"

TestEmbeddedRecorderStub::TestEmbeddedRecorderStub()
{
	m_value = 0;
}

TestEmbeddedRecorderStub::TestEmbeddedRecorderStub(int value)
    :    m_value(value)
{
    // Nothing todo so far.
}

TestEmbeddedRecorderStub::TestEmbeddedRecorderStub(const TestEmbeddedRecorderStub &obj)
{
    m_value = obj.m_value;
}

/** @} */
