/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    test
 * @{
 *
 * @brief      Test definition of the PortA as singleton
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_TESTS_PORTA_TESTPORTA_H_
#define SRC_TESTS_PORTA_TESTPORTA_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestPortA : public TestCase
{
public:
    /*
     * @brief Constructor.
     */
    TestPortA(int id, std::string brief) : TestCase(id, brief) { };
protected:
    /*
     * @brief
     */
    TEST(test1);

    // Must have.
    TEST_CASE_METHODS
};

#endif /* SRC_TESTS_PORTA_TESTPORTA_H_ */
/** @} */
